#include "Physics.hpp"

Physics::Physics()
{
	if(instance != nullptr)
		throw "Physics instantiated twice";
	instance = this;

	//world = new b2World(b2Vec2(0, -10));
}

Physics::~Physics()
{
	instance = nullptr;
	delete world;
}

void Physics::step()
{
	world->Step(1 / 60.f, 10, 10);
}
