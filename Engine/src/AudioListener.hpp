#pragma once
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <al.h>
#include <alc.h>
#include "Component.hpp"
#include "glm\glm.hpp"

using namespace std;

class AudioListener{
private:
	glm::vec3 position;
	glm::vec3 velocity;
};