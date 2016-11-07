#include "Engine.hpp"

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "SRE/SimpleRenderEngine.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/random.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "SceneParser.hpp"
#include "Transform.h"
#include "Rendering.h"
#include "Physics.hpp"
#include "PhysicsBody2D.hpp"
#include "BoxCollider2D.hpp"
#include "ParticleSystem.hpp"
#include <map>

using namespace SRE;
using namespace glm;

void Engine::setup() {
	physics = Physics::getInstance();
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
	//For testing particles
	map_gameObjects[10]->addComponent<ParticleSystem>();
	map_gameObjects[10]->getComponent<ParticleSystem>()->setSize(128);
	map_gameObjects[10]->getComponent<ParticleSystem>()->init();

	//Set up parent relationships between Transform components
	for (auto element : gameObjectDescriptors) {
		if (element.parentId != -1) {
			auto gameObject = map_gameObjects[element.uniqueId];
			auto parentGameObject = map_gameObjects[element.parentId];
			gameObject->getComponent<Transform>()->setParent(parentGameObject->getComponent<Transform>().get());
			
		}
	}


	auto camera = SimpleRenderEngine::instance->getCamera();
	camera->setPerspectiveProjection(60, 640, 480, 1, 1000);
	camera->lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto directionalLight = Light(LightType::Directional, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0, 20.0f);
	auto pointLight1 = Light(LightType::Point, glm::vec3(-1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 5, 20.0f);
	auto pointLight2 = Light(LightType::Point, glm::vec3(0,1,-2), glm::vec3(0, 0, 0), glm::vec3(3, 3, 3), 5, 20.0f);
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
        float deltaTimeSec = duration_cast<microseconds>(t2 - t1).count()/1000000.0f;
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

    // render game object
	for (auto & rendering : scene.getAllComponent<Rendering>()) {
		if(rendering) rendering->draw();
    }
	//for (auto & particleSystem : scene.getAllComponent<ParticleSystem>()) {
	//	if (particleSystem)
	//	{
	//		
	//		particleSystem->emit(glm::vec3(glm::sphericalRand<float>(250.0f)));
	//		particleSystem->update(deltaTimeSec);
	//		particleSystem->render();
	//	}

	//}
    SimpleRenderEngine::instance->swapWindow();
}
