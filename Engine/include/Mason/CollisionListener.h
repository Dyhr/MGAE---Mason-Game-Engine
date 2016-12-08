#pragma once
#include <Box2D/Box2D.h>
// Callbacks for derived classes.
namespace Mason {
	class CollisionListener : public b2ContactListener {
	public:

		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);
	};
}