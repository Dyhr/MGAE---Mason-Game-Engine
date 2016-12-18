#pragma once

#include <queue>
#include <map>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

namespace Mason {
	class Audio;

	class AudioManager {
	public:
		/** @brief Returns the currently active instance of AudioManager.
		*/
		static AudioManager* getInstance();
		/** @brief Is called once every frame. Plays any sounds that are in queue.
		*/
		void step();
		/** @brief Tries to play a sound immediately. If unsuccesful, the sound is added to the sourcesToBePlayed queue.
		*/
		void playAudioSource(Audio* audioComponent);
		/** @brief Loads an audio component into memory.
		*/
		bool loadAudioSource(Audio* audioComponent);
	private:
		AudioManager();
		~AudioManager();
		void cleanUp();
		void init(int channels = 16);
		static AudioManager* instance;
		std::queue<Audio*> sourcesToBePlayed;
		std::map<std::string, Mix_Chunk*> soundEffectMap;
		std::map<std::string, Mix_Music*> musicMap;
		bool initialized;
		int maxChannels;
	};
}