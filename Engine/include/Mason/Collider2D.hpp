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
		virtual float getScale() { return scale; };
		virtual void setScale(float scale_) { scale = scale; };
	protected:
		Collider2D(GameObject* gameObject) : Component(gameObject), shape(nullptr), density(1), friction(0.1f) { }
		
		float scale;

		friend class GameObject;
	};
}
