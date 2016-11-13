#pragma once
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <al.h>
#include <alc.h>
#include "glm\glm.hpp"
#include "Component.hpp"

using namespace std;

class AudioSource : public Component {
private:
	void playSound();
	//Between 0.0f and 1.0f
	float volume;
	glm::vec3 position;
	glm::vec3 velocity;
};