#include "Physics.hpp"

#include "GameObject.hpp"
#include "Transform.h"
#include "PhysicsBody2D.hpp"
#include "PhysicsBody.hpp"

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
