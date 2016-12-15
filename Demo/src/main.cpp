
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

		//marios
/*
		


		//bricks
		engine.scene->getGameObject(12)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(12)->addComponent<DangerousCollisions>();

		auto b = engine.scene->getGameObject(12)->addComponent<BoxCollider2D>();
		b->setSize(35, 40);

		engine.scene->getGameObject(13)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(13)->addComponent<DangerousCollisions>();
		auto b1 = engine.scene->getGameObject(13)->addComponent<BoxCollider2D>();
		b1->setSize(35, 40);

		engine.scene->getGameObject(14)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(14)->addComponent<DangerousCollisions>();
		auto b2 = engine.scene->getGameObject(14)->addComponent<BoxCollider2D>();
		b2->setSize(35, 40);

		engine.scene->getGameObject(15)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(15)->addComponent<DangerousCollisions>();
		auto b3 = engine.scene->getGameObject(15)->addComponent<BoxCollider2D>();
		b3->setSize(35, 40);
		engine.scene->getGameObject(16)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		engine.scene->getGameObject(16)->addComponent<DangerousCollisions>();
		auto b4 = engine.scene->getGameObject(16)->addComponent<BoxCollider2D>();
		b4->setSize(35, 40);
		//greentube
		engine.scene->getGameObject(17)->addComponent<PhysicsBody2D>()->body->SetType(b2BodyType::b2_kinematicBody);
		auto t = engine.scene->getGameObject(17)->addComponent<BoxCollider2D>();
		//engine.scene->getGameObject(17)->addComponent<PlayerController>();
		t->setSize(55, 45);
		*/
	


int main(int argc, char** argv) {

	Engine e;

	Script::scripts["dangerous-collisions"] = DangerousCollisions::Create;
	Script::scripts["player-controller"] = PlayerController::Create;

	e.loadScene("data/demoCollisions.json");
	e.start();

	return 0;
}
