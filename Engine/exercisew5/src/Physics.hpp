#pragma once

#include <vector>

#include <Box2D/Box2D.h>

class PhysicsBody;
class PhysicsBody2D;

class Physics
{
public:
	static Physics* instance;

	Physics();
	~Physics();

	b2World world = b2World(b2Vec2(0, -10));
	int velIterations = 10;
	int posIterations = 10;

	void step(float dt);
private:
	std::vector<PhysicsBody2D*> bodies2D;
	std::vector<PhysicsBody*> bodies;
	friend PhysicsBody2D;
	friend PhysicsBody;
};
