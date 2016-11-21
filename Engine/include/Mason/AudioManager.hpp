#pragma once

#include "Mason/Audio.hpp"

#include <vector>
#include <queue>

namespace Mason {
	class Audio;

	class AudioManager {
	public:
		static AudioManager* getInstance();
		void step();
		void AddAudioSource(Audio* audioComponent);
	private:
		AudioManager();
		void cleanUp();
		void init();
		static AudioManager* instance;
		std::vector<Audio*> sourcesToBePlayed;
		std::vector<Audio*> sourcesPlayed;
		std::queue<Audio*> sourcesToBePlayed1;
		std::queue<Audio*> sourcesPlayed1;
		bool initialized;
	};
}