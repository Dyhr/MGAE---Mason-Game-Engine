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
    void start();

	void loadScene(std::string path);

	Engine();
	~Engine();

	Scene scene;
private:
	void DebugUI();

    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	SRE::SimpleRenderEngine* sre;
	Physics* physics;
	AudioManager* audioManager;
	bool running, paused;
	SDL_Window *window;
};


