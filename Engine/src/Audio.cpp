#include "Mason/Audio.hpp"

#include <iostream>
#include <string>
#include <SDL_hints.h>
#include <SDL.h>

using namespace std;
using namespace Mason;

Audio::Audio(GameObject * gameObject) :Component(gameObject)
{
}

void Audio::init(string file, SoundType type, AudioManager * manager, int loops)
{
	this->manager = manager;
	path = file;
	this->type = type;
}

void Audio::play() {
	if (manager) {
		manager->PlayAudioSource(this);
	}
}