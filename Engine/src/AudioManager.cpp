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
	initialized = true;
	std::cout << "AudioManager initialized" << std::endl;
}

AudioManager::AudioManager() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void AudioManager::cleanUp()
{
	Mix_CloseAudio();
	initialized = false;
}

void AudioManager::step()
{
	if (!initialized) {
		init();
	}	

	for (int i = 0; i < 8; i++) {
		if (sourcesToBePlayed.empty()) break;
		auto audio = sourcesToBePlayed.front();
		if (audio->type == SoundType::EFFECT) {
			auto soundEffect = Mix_LoadWAV(audio->path.c_str());
			if (soundEffect != NULL) {
				Mix_PlayChannel(i, soundEffect, 0);
				sourcesToBePlayed.pop();
			}
		}
		else if (audio->type == SoundType::MUSIC) {
			auto music = Mix_LoadMUS(audio->path.c_str());
			if (music != NULL && Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(music, -1);
				sourcesToBePlayed.pop();
			}
		}		
	}
}

void AudioManager::AddAudioSource(Audio * audioComponent)
{
	sourcesToBePlayed.push(audioComponent);
}
