#pragma once

#include "Mason/AudioManager.hpp"
#include "Mason/Component.hpp"

namespace Mason {
	class AudioManager;
	enum SoundType {
		EFFECT, MUSIC
	};

	class Audio : public Component {
	public:
		void init(std::string file, SoundType type, AudioManager* manager, int loops = 0);
		SoundType type;
		std::string path;
		void play();		
	protected:
		Audio(std::shared_ptr<GameObject> gameObject);
		friend class GameObject;
	private:
		int loops;
		AudioManager *manager;
	};
}
