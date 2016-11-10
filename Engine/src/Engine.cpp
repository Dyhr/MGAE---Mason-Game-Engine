#include "Engine.hpp"

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE\Mesh.hpp>
#include <SRE\Shader.hpp>
#include <SRE\SimpleRenderEngine.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\random.hpp>
#include <glm\gtx\euler_angles.hpp>
#include "SceneParser.hpp"
#include "Transform.h"
#include "Rendering.h"
#include "Physics.hpp"
#include "PhysicsBody2D.hpp"
#include "BoxCollider2D.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleSystem.hpp"
#include <map>
#include "Script.hpp"
#include "Time.hpp"
#include <SDL.h>
#include "PlayerController.hpp"
#include <SRE\SimpleRenderEngine.hpp>
using namespace SRE;
using namespace glm;

void Engine::setup() {
	physics = Physics::getInstance();
	particleSystem = new ParticleSystem(1024);
	std::map<int, std::shared_ptr<GameObject>> map_gameObjects;

	std::vector<GameObjectDescriptor> gameObjectDescriptors = SceneParser::parseFile("data/car_house_tree.json");
	Shader* shader = Shader::getStandard();
	auto cubeMesh = Mesh::createCube();
	auto planeMesh = Mesh::createQuad();
	auto sphereMesh = Mesh::createSphere();
	for (auto element : gameObjectDescriptors) {
		Mesh* mesh;
		if (element.meshName == "sphere") 
			mesh = sphereMesh;
		else if (element.meshName == "cube") 
			mesh = cubeMesh;
		else if (element.meshName == "plane") 
			mesh = planeMesh;
		else
			throw "Undefined mesh";

		auto gameObject = scene.addGameObject(element.meshName);
		auto transformComponent = gameObject->addComponent<Transform>();
		auto renderingComponent = gameObject->addComponent<Rendering>();

		renderingComponent->loadMesh(std::make_shared<Mesh>(*mesh));
		renderingComponent->loadShader(std::make_shared<Shader>(*shader));
		renderingComponent->setColor(element.color);
		transformComponent->setPosition(element.position);
		transformComponent->setRotation(element.rotationEuler);
		transformComponent->setScale(element.scale);

		map_gameObjects[element.uniqueId] = gameObject;
		
	}

	//Set up parent relationships between Transform components
	for (auto element : gameObjectDescriptors) {
		if (element.parentId != -1) {
			auto gameObject = map_gameObjects[element.uniqueId];
			auto parentGameObject = map_gameObjects[element.parentId];
			gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>().get());
			
		}
	}

//<<<<<<< HEAD
//=======
//	map_gameObjects[0]->addComponent<PlayerController>();
//
//
//>>>>>>> 51a41ab4beb74fe256d36c7bd31219aa103f90b6
	auto camera = SimpleRenderEngine::instance->getCamera();
	camera->setPerspectiveProjection(60, 640, 480, 1, 1000);
	camera->lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	auto directionalLight = Light(LightType::Directional, vec3(0, 0, 0), vec3(1, 1, 1), vec3(1, 1, 1), 0, 20.0f);
	auto pointLight1 = Light(LightType::Point, vec3(-1, 1, 1), vec3(0, 0, 0), vec3(5, 0, 0), 5, 20.0f);
	auto pointLight2 = Light(LightType::Point, vec3(0,1,-2), vec3(0, 0, 0), vec3(3, 3, 3), 5, 20.0f);
	SimpleRenderEngine::instance->setLight(0, directionalLight);
	SimpleRenderEngine::instance->setLight(1, pointLight1);
	SimpleRenderEngine::instance->setLight(2, pointLight2);
   
}

void Engine::start() {
	physics->init();

    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    int timePerFrameMillis = 1000/60;
    while (true) {
		using namespace std::chrono;

        auto t2 = Clock::now();
        // time since last update
        int deltaTimeMicSec = duration_cast<microseconds>(t2 - t1).count();
		float deltaTimeSec = deltaTimeMicSec / 1000000.0f;

		// Set the time
		Time::getInstance()->update(deltaTimeMicSec/1000);

		// Update the engine
        update(deltaTimeSec);

        int updateTimeMillis = static_cast<int>(duration_cast<milliseconds>(Clock::now() - t2).count());
        int wait = timePerFrameMillis - updateTimeMillis;
        if (wait > 0){
            SDL_Delay(wait);
        }
        t1 = t2;
    }
}

void Engine::update(float deltaTimeSec) {
    SimpleRenderEngine::instance->clearScreen({0,0,1,1});

	// step the physics
	physics->step(deltaTimeSec);

	// fetch input
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {	// TODO gamepad support?
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:
			for (auto & script : scene.getAllComponent<Script>()) 
				if (script) script->OnInput(event);
			break;
		case SDL_QUIT:
			break;
		default: break;
		}
	}

	// update scripts
	for (auto & script : scene.getAllComponent<Script>()) {
		if (!script->started) {
			script->started = true;
			script->OnStart();
		}
		if (script) script->OnUpdate();
	}

    // render game object

	for (auto & rendering : scene.getAllComponent<Rendering>()) {
		if (rendering) {
			rendering->draw();
		}
    }

	for (auto & particleEmitter : scene.getAllComponent<ParticleEmitter>()) {
		if (particleEmitter) {
			particleEmitter->emit();
		}
	}

	particleSystem->update(deltaTimeSec);
	particleSystem->render();

    SimpleRenderEngine::instance->swapWindow();
}
