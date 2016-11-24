#pragma once
#include "Mason/Engine.hpp"
#include <map>

namespace Mason {
	class Config
	{
	public:
		static int* addInt(std::string name, int value);
		static float* addFloat(std::string name, float value);
		static std::string* addString(std::string name, std::string value);
		static int* getInt(std::string name);
		static float* getFloat(std::string name);
		static std::string* getString(std::string name);

		static void init();
		~Config();
	private:
		static Config* instance;

		std::map<std::string, int*> ints;
		std::map<std::string, float*> floats;
		std::map<std::string, std::string*> strings;

		friend class Engine;
	};
}
