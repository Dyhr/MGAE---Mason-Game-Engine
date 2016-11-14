#pragma once
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <al.h>
#include <alc.h>
#include "glm\glm.hpp"
#include "Component.hpp"

using namespace std;
class AudioMaster {
public:
	float volume;
	glm::vec3 position;
	glm::vec3 velocity;
	void init();
	void cleanUp();
	int playSound();
	int endWithError(char* msg);
private:
	ALCdevice *device;
	ALCcontext *context;
	ALuint *buffers;
	ALuint *sources;
	ALint source_state;
};