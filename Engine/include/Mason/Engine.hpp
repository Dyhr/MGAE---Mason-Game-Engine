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
	SRE::SimpleRenderEngine* sre;
	Physics* physics;
	AudioManager* audioManager;
	bool running;
	SDL_Window *window;
};


