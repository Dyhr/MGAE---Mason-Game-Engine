#pragma once

#include <SDL.h>
#include <vector>

namespace Mason {
	class Engine;

	class InputManager {
	public:
		static InputManager* getInstance();

		void Handle(Engine* engine);
		void Subscribe(void(*action)(SDL_Event)); // TODO unsubscribtion
	private:
		static InputManager* instance;

		std::vector<void(*)(SDL_Event)> subscribers;

		friend class Engine;
	};
}
