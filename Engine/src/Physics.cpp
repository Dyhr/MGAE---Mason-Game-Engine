#include "Mason/Physics.hpp"

#include "Mason/GameObject.hpp"
#include "Mason/Transform.h"
#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Collider2D.hpp"
#include "Mason/SREDebugDraw.h"
#include "Mason\CollisionListener.h"

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
		if(transform)
			transform->setPosition(glm::vec3(pos.x,pos.y,0));
			
		
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

		auto colliders = body->getGameObject()->getComponents<Collider2D>();
		for(auto collider : colliders){
			b2FixtureDef fd;
			fd.shape = collider->shape;
			fd.density = collider->density;
			fd.friction = collider->friction;
			body->body->CreateFixture(&fd)->SetUserData((void*)collider->getGameObject()); //our body is a container for the body we get from box2D
		}
	}
		//b2PolygonShape Mario;
		//Mario.SetAsBox(2, 2, b2Vec2(0, 0), 0.0f);
		
		
}
