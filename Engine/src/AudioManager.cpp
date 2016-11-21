#include "Mason/AudioManager.hpp"

#include <SDL.h>
#include <iostream>

using namespace Mason;

AudioManager* AudioManager::instance = nullptr;	

AudioManager * AudioManager::getInstance()
{
	if (instance) {
	}
	else {
		instance = new AudioManager();
		instance->initialized = false;
	}
	return instance;
	
}


void AudioManager::init()
{
	//Set max size of sourcesToBePlayed ? ?
	if (SDL_Init(SDL_INIT_AUDIO) < 0) 
		return;
	initialized = true;
}

AudioManager::AudioManager() {
}

void AudioManager::cleanUp()
{
	SDL_CloseAudio();
	initialized = false;
}

void AudioManager::step()
{
	if (initialized) {
		if (sourcesToBePlayed1.size() < 1 && sourcesPlayed1.size() < 1) {
			cleanUp();
		}
	}
	else {
		init();
	}	
	while(sourcesToBePlayed1.size() > 0) {
		auto audio = sourcesToBePlayed1.front();
		audio->play();
		sourcesToBePlayed1.pop();
		sourcesPlayed1.push(audio);
	}

	for (Uint32 i = 0; i < sourcesPlayed1.size();) {
		auto audio = sourcesPlayed1.front();
		if (audio->isDone()) {
			audio->cleanUp();
			sourcesPlayed1.pop();
		}
		else {
			i++;
		}
	}
}

void AudioManager::AddAudioSource(Audio * audioComponent)
{
	sourcesToBePlayed1.push(audioComponent);
}
