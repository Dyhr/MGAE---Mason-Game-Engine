#pragma once

#include "Component.hpp"
#include "AudioManager.hpp"

class AudioManager;

class Audio : public Component {
public: 
	void play();
	void cleanUp();
	void init(std::string file, AudioManager * manager);
	bool isPlaying();
	bool isDone();
	void query();
protected:
	Audio(GameObject *gameObject);
	friend class GameObject;
private:
	std::string path;
	AudioManager *manager;
};