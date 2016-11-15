#pragma once
#include <vector>
#include "Audio.hpp"
class AudioManager {
public:
	AudioManager & getInstance();
	void init();
	void cleanUp();
	void step();
	void AddAudioSource(Audio* audioComponent);
private:
	AudioManager() {};
	std::vector<Audio*> sourcesToBePlayed;
};