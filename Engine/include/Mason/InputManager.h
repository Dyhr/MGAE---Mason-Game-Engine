#pragma once

#include <SDL.h>

namespace Mason {
	class InputManager {
	public:

		InputManager();
		static InputManager* getInstance();
		void KeyDown(SDL_Event event);
		bool toggleGUI;
	private:
		static InputManager* instance;

	};
}