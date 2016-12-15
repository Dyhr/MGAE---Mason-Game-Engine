#pragma once

#include "Component.hpp"
#include "Physics.hpp"

namespace Mason {
	class PhysicsBody2D : public Component {
	public:
		~PhysicsBody2D();
		b2Body* body;

	protected:
		PhysicsBody2D(GameObject* gameObject);
		void UpdateFixtures();
		friend class GameObject;
		friend class Physics;
		friend class CircleCollider2D;
		friend class BoxCollider2D;
	};
}
