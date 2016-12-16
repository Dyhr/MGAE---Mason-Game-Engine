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

		float phScale = 400;
		
		friend class PhysicsBody2D;
		friend class Engine;
		friend class Transform;
		friend class Scene;
		friend class SREDebugDraw;
		friend class CircleCollider2D;
		friend class BoxCollider2D;
	};
}
