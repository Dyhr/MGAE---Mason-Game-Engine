#include "Mason/Physics.hpp"

#include "Mason/GameObject.hpp"
#include "Mason/Transform.h"
#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Collider2D.hpp"
#include "Mason/SREDebugDraw.h"
#include "Mason/CollisionListener.h"

#include "Box2D/Box2D.h"

using namespace Mason;

Physics* Physics::instance = nullptr;


Physics::Physics()
{
	world = new b2World(b2Vec2(0, -10));
	collisionListener = std::make_shared<CollisionListener>();
	world->SetContactListener(collisionListener.get());
	auto debugDraw = new SREDebugDraw();
	world->SetDebugDraw(debugDraw);
	debugDraw->SetFlags(b2Draw::e_shapeBit/* | b2Draw::e_aabbBit*/);
}

Physics::~Physics()
{
	delete world;
}

Physics* Physics::getInstance()
{
	instance = new Physics();
	return instance;
}

void Physics::step(float dt)
{
	world->Step(dt, velIterations, posIterations);
	for (auto body : bodies)
	{
		if (body->getGameObject()->destroyed) continue;
		auto transform = body->getGameObject()->getComponent<Transform>();
		auto pos = body->body->GetWorldCenter();
		auto angle = body->body->GetAngle() * (180/M_PI);
		if (transform) {
			transform->position = glm::vec3(pos.x*phScale, pos.y*phScale, 0);
			transform->rotation = float(angle);
			transform->transformize();
		}
	}
}
