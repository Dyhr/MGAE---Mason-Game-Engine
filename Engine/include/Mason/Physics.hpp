#pragma once

#include <vector>

#include <Box2D/Box2D.h>
#include <glm/vec2.hpp>

namespace Mason {
	class PhysicsBody2D;

	class Physics
	{
	public:
		static Physics* getInstance();

		b2World world = b2World(b2Vec2(0, -10));
		int velIterations = 10;
		int posIterations = 10;

	private:
		static Physics* instance;

		void step(float dt);

		Physics();

		std::vector<PhysicsBody2D*> bodies;
		friend class PhysicsBody2D;
		friend class Engine;
	};
}
