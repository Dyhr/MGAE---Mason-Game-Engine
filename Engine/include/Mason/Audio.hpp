#pragma once

#include "Mason/AudioManager.hpp"
#include "Mason/Component.hpp"
#include <string>

namespace Mason {
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
}
