#include "Mason/Physics.hpp"

#include "Mason/GameObject.hpp"
#include "Mason/Transform.h"
#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Collider2D.hpp"
#include "Mason/SREDebugDraw.h"
#include "Mason/CollisionListener.h"

using namespace Mason;

Physics* Physics::instance = nullptr;


Physics::Physics()
{
	auto collisionL = new CollisionListener();
	world.SetContactListener(collisionL);
	auto debugDraw = new SREDebugDraw();
	world.SetDebugDraw(debugDraw);
	debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
}

Physics* Physics::getInstance()
{
	instance = new Physics();
	return instance;
}

void Physics::step(float dt)
{
	world.Step(dt, velIterations, posIterations);
	for (auto body : bodies)
	{
		auto transform = body->getGameObject()->getComponent<Transform>();
		auto pos = body->body->GetWorldCenter();
		auto angle = body->body->GetAngle() * (180/M_PI);
		if (transform) {
			transform->position = glm::vec3(pos.x, pos.y, 0);
			transform->rotation = glm::vec3(0, 0, angle);
			transform->transformize();
		}
			
		
	}
	world.DrawDebugData();
	
}

void Physics::init()
{
	for(auto body : bodies) {
		auto transform = body->getGameObject()->getComponent<Transform>();
		if(transform) {
			auto pos = transform->getPosition();
			body->body->SetTransform(b2Vec2(pos.x, pos.y), 0);
		}

		body->UpdateFixtures();
	}
		
		
}
