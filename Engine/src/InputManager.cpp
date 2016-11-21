#include "Mason/InputManager.h"

#include "Mason/Engine.hpp"
#include "Mason/Script.hpp"
#include <iostream>


using namespace Mason;


InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance()
{
	if (instance == nullptr) instance = new InputManager();
	return instance;
}

void InputManager::Handle(Engine* engine)
{
	// fetch input
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_KEYDOWN:
			if (char(event.key.keysym.sym) == 'p') engine->showDebugGUI = !engine->showDebugGUI;
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			for (auto s : subscribers) s(event);

			for (auto & script : engine->scene->getAllComponent<Script>())
				if (script) script->OnInput(event);
			break;
		case SDL_QUIT:
			engine->running = false;
			break;
		default: break;
		}
	}
}

void InputManager::Subscribe(void(* action)(SDL_Event))
{
	subscribers.push_back(action);
}
