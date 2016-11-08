#pragma once

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Physics.hpp"
#include "ParticleSystem.hpp"

class Engine {
public:
    void setup();
    void start();
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	Scene scene;
	Physics* physics;
	ParticleSystem* particleSystem;
	bool running;
};


