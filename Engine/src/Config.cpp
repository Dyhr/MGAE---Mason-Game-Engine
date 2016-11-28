#include "Mason/Config.hpp"

using namespace Mason;

Config* Config::instance = nullptr;


int* Config::addInt(std::string name, int value)
{
	int* p = new int();
	*p = value;
	instance->ints[name] = p;
	return p;
}
float* Config::addFloat(std::string name, float value)
{
	float* p = new float();
	*p = value;
	instance->floats[name] = p;
	return p;
}
std::string* Config::addString(std::string name, std::string value)
{
	std::string* p = new std::string();
	*p = value;
	instance->strings[name] = p;
	return p;
}
int* Config::getInt(std::string name)
{
	std::map<std::string, int*>::iterator it = instance->ints.find(name);
	if (it == instance->ints.end()) addInt(name, 0);
	return instance->ints[name];
}
float* Config::getFloat(std::string name)
{
	std::map<std::string, float*>::iterator it = instance->floats.find(name);
	if (it == instance->floats.end()) addFloat(name, 0.0f);
	return instance->floats[name];
}
std::string* Config::getString(std::string name)
{
	std::map<std::string, std::string*>::iterator it = instance->strings.find(name);
	if (it == instance->strings.end()) addString(name, "");
	return instance->strings[name];
}

void Config::init()
{
	instance = new Config();
}

Config::~Config()
{
	for (auto i : ints)
		delete i.second;
	for (auto i : floats)
		delete i.second;
	for (auto i : strings)
		delete i.second;
}
