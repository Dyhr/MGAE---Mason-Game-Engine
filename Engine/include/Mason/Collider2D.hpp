#pragma once
#include "Component.hpp"
#include "Physics.hpp"

namespace Mason {
	class Collider2D : public Component
	{
	public:
		b2Shape* shape;
		float density;
		float friction;
		virtual b2Vec2 GetScale() = 0;
	protected:
		Collider2D(GameObject* gameObject) : Component(gameObject), shape(nullptr), density(1), friction(0.1f) { }
		
		friend class GameObject;
	};
}
