#pragma once

#include "Component.hpp"
#include "Physics.hpp"

namespace Mason {
	class PhysicsBody2D : public Component {
	public:
		~PhysicsBody2D();
		void UpdateFixtures();
		b2Body* body;

	protected:
		PhysicsBody2D(GameObject* gameObject);
		friend class GameObject;
	};
}
