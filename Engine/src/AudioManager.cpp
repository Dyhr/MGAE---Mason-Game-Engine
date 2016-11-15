#include "AudioManager.hpp"
#include <SDL.h>

AudioManager & AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}


void AudioManager::init()
{
	//Set max size of sourcesToBePlayed ? ?


	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return;
}

void AudioManager::cleanUp()
{
	SDL_CloseAudio();
}

void AudioManager::step()
{
	for (auto & audio : sourcesToBePlayed) {
		if (!audio->isPlaying()) {
			audio->play();
		}
	}
	for (int i = 0; i < sourcesToBePlayed.size();) {
		if (!sourcesToBePlayed[i]->isPlaying()) {
			sourcesToBePlayed.erase(sourcesToBePlayed.begin() + i);
		}
		else {
			i++;
		}
	}
}

void AudioManager::AddAudioSource(Audio * audioComponent)
{
	sourcesToBePlayed.push_back(audioComponent);
}
