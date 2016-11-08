#include "Engine2D.h"

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
#include "SpriteRenderer.h"
#include "Physics.hpp"
#include "PhysicsBody2D.hpp"
#include "BoxCollider2D.hpp"

using namespace SRE;

void Engine2D::setup() {
	GameObject* gameObject = new GameObject("sprite");

	physics = Physics::getInstance();
	Texture* texture = Texture::createFromFile("data/number_puzzle.png", false);
	texture->setFilterSampling(false);

	SpriteRenderer number2_pivot0_0(170 * 2, 0, 170, 128, 0, 0, texture, &r);
	SpriteRenderer number2_pivot1_1(170 * 2, 0, 170, 128, 1, 1, texture, &r);
	SpriteRenderer number2_pivot05_05(170 * 2, 0, 170, 128, 0.5f, 0.5f, texture, &r);

	number2_pivot0_0.draw(glm::vec2(170 * 2, 128));
	number2_pivot1_1.draw(glm::vec2(170 * 2, 128));
	number2_pivot05_05.draw(glm::vec2(170 * 2, 128));

	r.swapWindow();

		auto transformComponent = gameObject->addComponent<Transform>();
		auto renderingComponent = gameObject->addComponent<SpriteRenderer>();

		transformComponent->setPosition(element.position);
		transformComponent->setRotation(element.rotationEuler);
		transformComponent->setScale(element.scale);


	auto camera = SimpleRenderEngine::instance->getCamera();
	camera->setPerspectiveProjection(60, 640, 480, 1, 1000);
	camera->lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto directionalLight = Light(LightType::Directional, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0, 20.0f);
	auto pointLight1 = Light(LightType::Point, glm::vec3(-1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(5, 0, 0), 5, 20.0f);
	auto pointLight2 = Light(LightType::Point, glm::vec3(0, 1, -2), glm::vec3(0, 0, 0), glm::vec3(3, 3, 3), 5, 20.0f);
	SimpleRenderEngine::instance->setLight(0, directionalLight);
	SimpleRenderEngine::instance->setLight(1, pointLight1);
	SimpleRenderEngine::instance->setLight(2, pointLight2);

}

void Engine2D::start() {
	physics->init();

	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();
	int timePerFrameMillis = 1000 / 60;
	while (true) {
		using namespace std::chrono;

		auto t2 = Clock::now();
		// time since last update
		float deltaTimeSec = duration_cast<microseconds>(t2 - t1).count() / 1000000.0f;
		update(deltaTimeSec);

		int updateTimeMillis = static_cast<int>(duration_cast<milliseconds>(Clock::now() - t2).count());
		int wait = timePerFrameMillis - updateTimeMillis;
		if (wait > 0) {
			SDL_Delay(wait);
		}
		t1 = t2;
	}
}

void Engine2D::update(float deltaTimeSec) {
	SimpleRenderEngine::instance->clearScreen({ 0,0,1,1 });

	// step the physics
	physics->step(deltaTimeSec);

	// render game object
	for (auto & go : gameObjects) {
		auto rendering = go.get()->getComponent<Rendering>();
		if (rendering) rendering->draw();
	}
	SimpleRenderEngine::instance->swapWindow();
}
