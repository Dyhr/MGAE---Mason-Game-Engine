#include "Physics.hpp"

Physics::Physics()
{
	world = b2World(b2Vec2(0, -10));
}

void Physics::step(float dt)
{
	world.Step(dt, velIterations, posIterations);
}
