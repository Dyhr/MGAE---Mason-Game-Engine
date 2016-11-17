#pragma once

#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"
#include "AudioManager.hpp"
#include <SDL.h>

class Engine {
public:
    void setup();
    void start();

	Engine();
	~Engine();

	Scene scene;
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	Physics* physics;
	AudioManager* audioManager;
	bool running;
	SDL_Window *window;
};


