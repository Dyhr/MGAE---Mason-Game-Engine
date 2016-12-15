#include "Mason/AudioManager.hpp"

#include <SDL.h>
#include <iostream>

using namespace Mason;

AudioManager* AudioManager::instance = nullptr;	

std::map<int, Mix_Chunk*> channelsPlaying;

AudioManager * AudioManager::getInstance()
{
	if (instance) {
	}
	else {
		instance = new AudioManager();
		instance->init();
	}
	return instance;	
}

void channelDone(int channel) {
	std::cout << "Freeing chunk for channel: " << channel << std::endl;
	Mix_FreeChunk(channelsPlaying[channel]);
	channelsPlaying[channel] = nullptr;
}

void AudioManager::init()
{
	//Set max size of sourcesToBePlayed ? ?
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_ChannelFinished(channelDone);
	initialized = true;
	//Allocate arbitrary channels for audio. TODO base on something, such as e.g. a multiple of the number of audiocomponents in a scene?
	Mix_AllocateChannels(16);
	maxChannels = Mix_AllocateChannels(-1);
	std::cout << "AudioManager initialized with " << maxChannels << " channels allocated." << std::endl;
}

AudioManager::AudioManager() {
	
}

Mason::AudioManager::~AudioManager() {
	cleanUp();
}

void AudioManager::cleanUp()
{
	for (int i = 0; i < channelsPlaying.size(); i++) {
		if (channelsPlaying[i]) {
			Mix_FreeChunk(channelsPlaying[i]);
		}
	}
	Mix_CloseAudio();
	initialized = false;
}

void AudioManager::step()
{	
	if (!initialized) {
		init();
	}	

	for (int i = 0; i < maxChannels; i++) {
		if (sourcesToBePlayed.empty()) break;
		if (channelsPlaying[i]) continue;
		auto audio = sourcesToBePlayed.front();
		if (audio->type == SoundType::EFFECT) {
			auto soundEffect = Mix_LoadWAV(audio->path.c_str());
			if (soundEffect != NULL) {
				Mix_PlayChannel(i, soundEffect, 0);				
				sourcesToBePlayed.pop();
				channelsPlaying[i] = soundEffect;
			}
			else {
				std::cout << "Bad Wav: " << audio->path.c_str() << std::endl;
			}
		}
		else if (audio->type == SoundType::MUSIC) {
			auto music = Mix_LoadMUS(audio->path.c_str());
			if (music != NULL && Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(music, -1);
				sourcesToBePlayed.pop();
			}
			else {
				std::cout << "Bad Wav: " << audio->path.c_str() << std::endl;
			}
		}		
	}
}

void AudioManager::PlayAudioSource(Audio * audioComponent)
{
	if (audioComponent->type == SoundType::EFFECT) {
		auto soundEffect = Mix_LoadWAV(audioComponent->path.c_str());
		if (soundEffect != NULL) {
			for (int i = 0; i < maxChannels; i++) {
				if (channelsPlaying[i] == nullptr) {
					Mix_PlayChannel(i, soundEffect, 0);
					channelsPlaying[i] = soundEffect;
					return;
				}
			}
		}
	}
	else if (audioComponent->type == SoundType::MUSIC) {
		auto music = Mix_LoadMUS(audioComponent->path.c_str());
		if (music != NULL && Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(music, -1);	
			return;
		}
	}
	sourcesToBePlayed.push(audioComponent);
}
