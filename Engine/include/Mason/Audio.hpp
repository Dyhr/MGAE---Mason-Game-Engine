#pragma once

#include "Mason/AudioManager.hpp"
#include "Mason/Component.hpp"
#include <string>
#include <SDL_mixer.h>

namespace Mason {
	class AudioManager;
	enum SoundType {
		EFFECT, MUSIC
	};

	class Audio : public Component {
	public:
		void init(std::string file, SoundType type, AudioManager * manager, int loops = 0);
		SoundType type;
		std::string path;
		void play();		
	protected:
		Audio(GameObject *gameObject);
		friend class GameObject;
	private:
		int loops;
		AudioManager *manager;
	};
}
