#pragma once

#include <queue>
#include <map>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

namespace Mason {
	class Audio;

	class AudioManager {
	public:
		static AudioManager* getInstance();
		void step();
		void playAudioSource(Audio* audioComponent);
		bool loadAudioSource(Audio* audioComponent);
	private:
		AudioManager();
		~AudioManager();
		void cleanUp();
		void init();
		static AudioManager* instance;
		std::queue<Audio*> sourcesToBePlayed;
		std::map<std::string, Mix_Chunk*> soundEffectMap;
		std::map<std::string, Mix_Music*> musicMap;
		bool initialized;
		int maxChannels;
	};
}