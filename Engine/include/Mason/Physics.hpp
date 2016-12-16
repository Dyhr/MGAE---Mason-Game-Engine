#pragma once

#include <vector>
#include <Box2D/Box2D.h>

namespace Mason {
	class PhysicsBody2D;
	class CollisionListener;
	/** @class Physics
	* @brief contains the physics world, with the the CollisionListener and the SREDebugDraw
	* built on the physics and collision library Box2D. A private method calls the world step to advance the time in physics world. That step should be constant on FPS delta time.
	*/
	class Physics
	{
	public:
		/** @return instance of the physics 
		*/
		static Physics* getInstance();

		b2World world = b2World(b2Vec2(0, -10)); ///< world with 2D physics we get from Box2D
		int velIterations = 10; ///< physics settings. the distance thebodies in the world move will be their velocity (in distance units per second) multiplied by the length of the step (in seconds)
		int posIterations = 10; ///< physics settings. affect the way bodies will react when they collide, together with the velocity

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
