
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/InputManager.h"
#include "PlayerController.hpp"

using namespace glm;
using namespace Mason;


Engine engine;

void loadScene(int index)
{
	switch (index)
	{
	case 0: {
		engine.loadScene("data/demo2.json");

		engine.scene->getGameObject(1)->addComponent<PlayerController>();

		break;
	}
	case 1: {
		engine.loadScene("data/demo1.json");

		auto emitter = engine.scene->getGameObject(2)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config1(8, 1, vec3(10, 5, 0), vec3(0, -20, 0));
		config1.setFixedSize(4.0f);
		config1.setLERPColor(vec4(0, 1, 0, 1), vec4(0, 1, 0, 0));
		config1.setFixedRotation(3.0f);
		emitter->init(config1);
		emitter->start();

		std::vector<glm::vec2> splinePoints;
		splinePoints.push_back(glm::vec2(0, 0));
		splinePoints.push_back(glm::vec2(0.25f, 1));
		splinePoints.push_back(glm::vec2(0.5f, 0.5));
		splinePoints.push_back(glm::vec2(0.85f, 0));
		splinePoints.push_back(glm::vec2(1, 1));

		emitter = engine.scene->getGameObject(3)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config2(15, 2, vec3(10, 10, 0), vec3(0, -10, 0));
		config2.setSplineInterpSize(0.5f, 4.0f, splinePoints);
		config2.setRandomColor(vec4(1, 1, 1, 1), vec4(0, 0, 0, 1));
		config2.setLERPRotation(0.0f, 1.6f);
		emitter->init(config2);
		emitter->start();

		emitter = engine.scene->getGameObject(4)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config3(2, 5, vec3(10, 5, 0), vec3(-10, 0, 0));
		config3.setFixedSize(1.0f);
		config3.setFixedColor(vec4(1, 0, 0, 1));
		config3.setSplineInterpColor(vec4(1, 0, 0, 1), vec4(0, 1, 0, 0), splinePoints);
		config3.setRandomRotation(0.3,1.2);
		emitter->init(config3);
		emitter->start();


		emitter = engine.scene->getGameObject(5)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config4(8, 2, vec3(-20, 5, 0), vec3(10, 0, 0));
		config4.setLERPSize(4.0, 0.0f);
		config4.setFixedColor(vec4(0, 1, 1, 1));
		emitter->init(config4);
		emitter->start();

		emitter = engine.scene->getGameObject(6)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config5(1, 2, vec3(-10, 5, 0), vec3(0, 0, 0));
		config5.setRandomSize(1.0f, 3.0f);
		config5.setFixedColor(vec4(1, 0, 1, 1));
		emitter->init(config5);
		emitter->start();

		emitter = engine.scene->getGameObject(7)->addComponent<ParticleEmitter>();
		ParticleEmitterConfig config6(2, 5, vec3(-10, 5, 0), vec3(10, 10, 0));
		config6.setFixedSize(1.0f);
		config6.setFixedColor(vec4(1, 1, 0, 1));
		emitter->init(config6);
		emitter->start();

		break;
	}
	default:
		throw "Unknown demo";
	}
}


int numScenes = 2;
int currentScene = 0;

void handleInput(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && char(event.key.keysym.sym) == ' ') {
		currentScene = (currentScene + 1) % numScenes;
		loadScene(currentScene);
	}
}

int main(int argc, char** argv) {

	InputManager::getInstance()->Subscribe(handleInput);

	loadScene(currentScene);

	engine.start();

	return 0;
}
