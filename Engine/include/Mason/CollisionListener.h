#pragma once
#include <Box2D/Box2D.h>
#include <vector>
#include "Collider2D.hpp"
#include "Script.hpp"

// Callbacks for derived classes.
namespace Mason {
	/** @class CollisionListener 
	* @brief detection to find new collisions 
	*/
	class CollisionListener : public b2ContactListener {
	public:
		void ProcessEvents();

		//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
	private:
		std::vector<std::tuple<Script*, GameObject*>> collisionEnters;
		std::vector<std::tuple<Script*, GameObject*>> collisionExits;
	};
}