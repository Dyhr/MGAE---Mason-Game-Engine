#pragma once
#include <Box2D/Box2D.h>
// Callbacks for derived classes.
namespace Mason {
	class CollisionListener {
	public:
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	};
}