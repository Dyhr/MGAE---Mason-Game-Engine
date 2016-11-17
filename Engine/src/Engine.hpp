#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"

#include <SDL.h>
#include "InputManage.h"

#include "AudioManager.hpp"


class Engine {
public:
	
	Engine::Engine(SDL_Window *window);
	int numberSprites;
	//InputManage* inp;

    void setup();
    void start();
	void Engine::DebugUI();

	
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	Scene scene;
	Physics* physics;

	bool running, paused;
	SDL_Window *window;

	AudioManager* audioManager;

};


