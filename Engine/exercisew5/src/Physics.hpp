#pragma once
#include <Box2D/Box2D.h>

class Physics
{
public:
	static Physics instance;

	b2World world;
	int velIterations = 10;
	int posIterations = 10;

	Physics();

	void step(float dt);
private:
};
