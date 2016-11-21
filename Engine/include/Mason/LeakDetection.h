#pragma once
#include <cstdint> //should be included where we call the function--Engine.cpp?
namespace Mason {
	class LeakDetection {

#ifdef _WIN32
		//define for Windows (32-bit and 64-bit)
	public:
		int64_t TotalVirtualMem();
		int64_t CurrentVirtualMem();
		int64_t VirtualMemByCurrentProccess();
		int64_t TotalPhysMem();
		int64_t CurrentPhysMem();
		int64_t PhysMemByCurrentProccess();

#elif __APPLE__ && __MACH__
		//code
	public:
		void TotalVirtualMem();
		void CurrentVirtualMem();
		void VirtualMemByCurrentProccess();
		void TotalPhysMem();
		void CurrentPhysMem();
		void PhysMemByCurrentProccess();
#else
#   error "Unknown compiler"
#endif

	};
}
