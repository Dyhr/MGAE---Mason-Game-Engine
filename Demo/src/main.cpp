
#include <Mason/Engine.hpp>
#include "Mason/ParticleEmitter.hpp"
#include "Mason/InputManager.h"
#include "PlayerController.hpp"
#include "Mason/CircleCollider2D.h"
#include "Mason/BoxCollider2D.hpp"
#include "Mason/PhysicsBody2D.hpp"
#include "DangerousCollisions.h"
using namespace glm;
using namespace Mason;


Engine engine;

void loadScene(int index)
{
	switch (index)
	{
	case 0: {
		//engine.loadScene("data/demo2.json");
		engine.loadScene("data/demoCollisions.json");
		//marios
		engine.scene->getGameObject(9)->addComponent<PlayerController>();
		engine.scene->getGameObject(9)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m = engine.scene->getGameObject(9)->addComponent<CircleCollider2D>();
		m->setSize(18);

		
		engine.scene->getGameObject(10)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m1 = engine.scene->getGameObject(10)->addComponent<CircleCollider2D>();
		m1->setSize(18);

		
		engine.scene->getGameObject(2)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m2 = engine.scene->getGameObject(2)->addComponent<CircleCollider2D>();
		m2->setSize(18);

		engine.scene->getGameObject(3)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m3 = engine.scene->getGameObject(3)->addComponent<CircleCollider2D>();
		m3->setSize(18);

		engine.scene->getGameObject(4)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_dynamicBody);
		auto m4 = engine.scene->getGameObject(4)->addComponent<CircleCollider2D>();
		m4->setSize(18);

		//bricks
		engine.scene->getGameObject(3)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(3)->addComponent<DangerousCollisions>();
		auto b = engine.scene->getGameObject(3)->addComponent<BoxCollider2D>();
		b->setSize(35, 35);

		engine.scene->getGameObject(4)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(4)->addComponent<DangerousCollisions>();
		auto b2 = engine.scene->getGameObject(4)->addComponent<BoxCollider2D>();
		b2->setSize(35, 40);

		engine.scene->getGameObject(5)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(5)->addComponent<DangerousCollisions>();
		auto b3 = engine.scene->getGameObject(5)->addComponent<BoxCollider2D>();
		b3->setSize(35, 40);

		engine.scene->getGameObject(6)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(6)->addComponent<DangerousCollisions>();
		auto b4 = engine.scene->getGameObject(6)->addComponent<BoxCollider2D>();
		b4->setSize(35, 40);

		engine.scene->getGameObject(7)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(7)->addComponent<DangerousCollisions>();
		auto b5 = engine.scene->getGameObject(7)->addComponent<BoxCollider2D>();
		b5->setSize(35, 40);

		//greentube
		engine.scene->getGameObject(8)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		auto b6 = engine.scene->getGameObject(8)->addComponent<BoxCollider2D>();
		b6->setSize(55, 45);


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
