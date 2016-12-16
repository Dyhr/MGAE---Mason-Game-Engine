#include "Mason/Audio.hpp"

#include <iostream>
#include <string>
#include <SDL_hints.h>
#include <SDL.h>

using namespace std;
using namespace Mason;

Audio::Audio(shared_ptr<GameObject> gameObject) :Component(gameObject)
{
}

void Audio::init(string file, SoundType type, AudioManager * manager, int loops)
{
	this->manager = manager;
	path = file;
	this->type = type;
	manager->loadAudioSource(this);
}

void Audio::play() {
	if (manager) {
		manager->playAudioSource(this);
	}
}