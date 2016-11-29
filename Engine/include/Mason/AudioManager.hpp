#pragma once

#include "Mason/Audio.hpp"

#include <vector>
#include <queue>
#include <SDL_mixer.h>
#include <map>
namespace Mason {
	class Audio;

	class AudioManager {
	public:
		static AudioManager* getInstance();
		void step();
		void AddAudioSource(Audio* audioComponent);
	private:
		AudioManager();
		~AudioManager();
		void cleanUp();
		void init();
		static AudioManager* instance;
		std::queue<Audio*> sourcesToBePlayed;
		bool initialized;
	};
}