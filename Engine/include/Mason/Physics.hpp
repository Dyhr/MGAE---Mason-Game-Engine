#pragma once

#include <vector>
#include <Box2D/Box2D.h>

namespace Mason {
	class PhysicsBody2D;
	class CollisionListener;

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

		std::shared_ptr<CollisionListener> collisionListener;
		std::vector<PhysicsBody2D*> bodies;
		
		friend class PhysicsBody2D;
		friend class Engine;
	};
}
