#pragma once

#define SDL_MAIN_HANDLED

#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"
#include "AudioManager.hpp"
#include <SDL.h>
#include <SRE/SimpleRenderEngine.hpp>
#include "Mason/Config.hpp"

namespace Mason {

	class Engine {
	public:
		void start();

		void loadScene(std::string path);

		Engine();
		~Engine();

		SRE::SimpleRenderEngine* sre; // TODO make this private once everything is implemented

		Scene* scene;
	private:
		void DebugUI();

		void update(float deltaTimeSec);
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		Physics* physics;
		AudioManager* audioManager;
		
		bool running, paused;
		bool showDebugGUI;
		int* windowWidth;
		int* windowHeight;
		SDL_Window *window;

		friend class InputManager;
	};
}


