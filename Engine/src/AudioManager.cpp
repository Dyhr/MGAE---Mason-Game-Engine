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
}

void AudioManager::init()
{
	//Set max size of sourcesToBePlayed ? ?
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_ChannelFinished(channelDone);
	initialized = true;
	std::cout << "AudioManager initialized" << std::endl;
}

AudioManager::AudioManager() {
	
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

void AudioManager::AddAudioSource(Audio * audioComponent)
{
	sourcesToBePlayed.push(audioComponent);
}

