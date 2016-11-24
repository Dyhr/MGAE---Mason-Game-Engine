#pragma once

#include <vector>

#include <Box2D/Box2D.h>

namespace Mason {
	class PhysicsBody2D;

	class Physics
	{
	public:
		static Physics* getInstance();

		b2World world = b2World(b2Vec2(0, -10));// -10 gravity, we want to be able to change it
		int velIterations = 10;
		int posIterations = 10;

		void step(float dt);
		void init();
	private:
		static Physics* instance;

		Physics();

		std::vector<PhysicsBody2D*> bodies;
		friend PhysicsBody2D;
	};
}
