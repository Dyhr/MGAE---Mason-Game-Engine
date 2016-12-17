#pragma once

#define SDL_MAIN_HANDLED

#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"
#include "AudioManager.hpp"
#include "Mason/Config.hpp"

struct SDL_Window;
class SRE::SimpleRenderEngine;

namespace Mason {

	
	/** @class Engine
	* @brief Brief about the engine.
	*
	* description of the engine
	*
	* @fn void start()
	* @brief about start, it initializes...
	*
	* @fn void loadScene(std::string path)
	
	*
	* @fn Engine()
	* @brief constructor
	* description of the constructor
	*
	* @fn ~Engine()
	* @brief destructor
	* description of the destructor
	*
	* @file demoCollisions.json
	*  This is the scene for the physics demo (not sure if this work)
	*  @verbinclude demoCollisions.json
	*/
	class Engine {

	public:
		void start();
		/**
		* @param path json file that contains the components
		*/
		void loadScene(std::string path);
		
		Engine();
		~Engine();

		Scene* scene; ///< The scene we load(brief description)
	private:
		void DebugUI();

		void update(float deltaTimeSec);
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		Physics* physics;
		SRE::SimpleRenderEngine* sre;
		AudioManager* audioManager;
		
		bool running, paused;
		bool showDebugGUI, showDebugPhysics; 
		int* windowWidth;
		int* windowHeight;
		SDL_Window* window;

		friend class InputManager;
	};
}


