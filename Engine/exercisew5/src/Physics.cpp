#include "Physics.hpp"

#include "GameObject.hpp"
#include "Transform.h"
#include "PhysicsBody2D.hpp"
#include "PhysicsBody.hpp"
#include "Collider2D.hpp"

Physics* Physics::instance = nullptr;

Physics::Physics()
{
	if(instance != nullptr) throw "Physics was instantiated twice";
	instance = this;
}

Physics::~Physics()
{
	instance = nullptr;
}

void Physics::step(float dt)
{
	world.Step(dt, velIterations, posIterations);
	for (auto body : bodies2D)
	{
		auto transform = body->getGameObject()->getComponent<Transform>();
		auto pos = body->body->GetWorldCenter();
		if(transform)
			transform->setPosition(glm::vec3(pos.x,0,pos.y));
	}
}

void Physics::init()
{
	for(auto body : bodies2D) {
		auto transform = body->getGameObject()->getComponent<Transform>();
		if(transform) {
			auto pos = transform->getPosition();
			body->body->SetTransform(b2Vec2(pos.x, pos.z), 0);
		}

		auto colliders = body->getGameObject()->getComponents<Collider2D>();
		for(auto collider : colliders){
			b2FixtureDef fd;
			fd.shape = collider->shape;
			fd.density = collider->density;
			fd.friction = collider->friction;
			body->body->CreateFixture(&fd);
		}
	}
}
