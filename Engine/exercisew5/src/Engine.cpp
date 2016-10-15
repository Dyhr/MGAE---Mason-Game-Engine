#include "Engine.hpp"

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "SRE/SimpleRenderEngine.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "SceneParser.hpp"
#include "Transform.h"
#include "Rendering.h"
#include "Physics.hpp"

using namespace SRE;

void Engine::setup() {
	std::vector<GameObjectDescriptor> scene = SceneParser::parseFile("data/car_house_tree.json");
	Shader* shader = Shader::getStandard();
	auto cubeMesh = Mesh::createCube();
	auto planeMesh = Mesh::createQuad();
	auto sphereMesh = Mesh::createSphere();
	for (auto element : scene) {
		Mesh* mesh;
		if (element.meshName == "sphere") 
			mesh = sphereMesh;
		else if (element.meshName == "cube") 
			mesh = cubeMesh;
		else if (element.meshName == "plane") 
			mesh = planeMesh;
		else
			throw "Undefined mesh";

		auto gameObject = std::make_shared<GameObject>(element.meshName);
		auto transformComponent = gameObject->addComponent<Transform>();
		auto renderingComponent = gameObject->addComponent<Rendering>();
		renderingComponent->loadMesh(std::make_shared<Mesh>(*mesh));
		renderingComponent->loadShader(std::make_shared<Shader>(*shader));
		renderingComponent->setColor(element.color);
		transformComponent->setPosition(element.position);
		transformComponent->setRotation(element.rotationEuler);
		transformComponent->setScale(element.scale);

		if (element.parentId != -1) {
			transformComponent->setParent(gameObjects[element.parentId].get()->getComponent<Transform>().get());
		}

		gameObjects.push_back(gameObject);
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
            SDL_Delay( wait );
        }
        t1 = t2;
    }
}

void Engine::update(float deltaTimeSec) {
    SimpleRenderEngine::instance->clearScreen({0,0,1,1});

	// step the physics
	Physics::instance.step(deltaTimeSec);

    // render game object
    for (auto & go : gameObjects){
		auto rendering = go.get()->getComponent<Rendering>();
		if(rendering) rendering->draw();
    }
    SimpleRenderEngine::instance->swapWindow();
}
