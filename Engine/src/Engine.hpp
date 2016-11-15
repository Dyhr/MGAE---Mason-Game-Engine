#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"
#include <SDL.h>
#include "InputManage.h"

class Engine {
public:
	Engine::Engine(SDL_Window *window);
	int numberSprites;

    void setup();
    void start();
	void Engine::DebugUI();

	
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	Scene scene;
	Physics* physics;
	bool running;
	SDL_Window *window;
};


