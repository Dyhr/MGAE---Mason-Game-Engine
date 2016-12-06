
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/InputManager.h"
#include "PlayerController.hpp"
#include "Mason/CircleCollider2D.h"
#include "Mason/BoxCollider2D.hpp"
#include "Mason/PhysicsBody2D.hpp"

using namespace glm;
using namespace Mason;


Engine engine;

void loadScene(int index)
{
	switch (index)
	{
	case 0: {
		engine.loadScene("data/demo2.json");
		//mario
		engine.scene->getGameObject(2)->addComponent<PlayerController>();
		engine.scene->getGameObject(2)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m = engine.scene->getGameObject(2)->addComponent<CircleCollider2D>();
		m->setSize(18);

		//bricks
		engine.scene->getGameObject(3)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		auto b = engine.scene->getGameObject(3)->addComponent<BoxCollider2D>();
		b->setSize(35, 35);

		engine.scene->getGameObject(4)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		auto b2 = engine.scene->getGameObject(4)->addComponent<BoxCollider2D>();
		b2->setSize(35, 40);

		break;
	}
	case 1: {
		engine.loadScene("data/demo1.json");
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
