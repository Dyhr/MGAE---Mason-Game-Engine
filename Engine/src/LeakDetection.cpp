#include "Mason/LeakDetection.h"

#include <cstdint>


#ifdef _WIN32
//define for Windows (32-bit and 64-bit)

#include "windows.h"
#include "psapi.h"
#include "TCHAR.h"
#include "pdh.h"

using namespace Mason;

int64_t LeakDetection::TotalVirtualMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	//float result = *(float*)&totalVirtualMem;
	return totalVirtualMem/(1024*1024);//from bits to Mb
}

int64_t LeakDetection::CurrentVirtualMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
	return virtualMemUsed/ (1024 * 1024);
}
int64_t LeakDetection::VirtualMemByCurrentProccess() {

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	return virtualMemUsedByMe / (1024 * 1024);
}


int64_t LeakDetection::TotalPhysMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
	return totalPhysMem / (1024 * 1024);
}
int64_t LeakDetection::CurrentPhysMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	return physMemUsed / (1024 * 1024);
}

int64_t LeakDetection::PhysMemByCurrentProccess() {

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	return physMemUsedByMe / (1024 * 1024);
}

#elif __APPLE__ && __MACH__
//code
#include "sysctl.h"
#include<mach/mach.h>

xsw_usage vmusage = { 0 };
size_t size = sizeof(vmusage);
if (sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0) != 0)
{
	perror("unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)");
}
void LeakDetection::TotalVirtualMem() {
	struct statfs stats;
	if (0 == statfs("/", &stats))
	{
		myFreeSwap = (uint64_t)stats.f_bsize * stats.f_bfree;
	}
}

void LeakDetection::CurrentVirtualMem() {
	xsw_usage vmusage = { 0 };
	size_t size = sizeof(vmusage);
	if (sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0) != 0)
	{
		perror("unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)");
	}
}

void LeakDetection::VirtualMemByCurrentProccess() {
	struct task_basic_info t_info;
	mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

	if (KERN_SUCCESS != task_info(mach_task_self(),
		TASK_BASIC_INFO, (task_info_t)&t_info,
		&t_info_count))
	{
		return -1;
	}
	
	// virtual size is in t_info.virtual_size;
}


void LeakDetection::TotalPhysMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
}
void LeakDetection::CurrentPhysMem() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
}

void LeakDetection::PhysMemByCurrentProccess() {
	struct task_basic_info t_info;
	mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

	if (KERN_SUCCESS != task_info(mach_task_self(),
		TASK_BASIC_INFO, (task_info_t)&t_info,
		&t_info_count))
	{
		return -1;
}
	// resident size is in t_info.resident_size;
	
}

#else
#   error "Unknown compiler"
#endif
