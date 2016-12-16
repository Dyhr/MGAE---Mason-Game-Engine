#pragma once
#include "Component.hpp"
#include "Physics.hpp"

namespace Mason {
	class Collider2D : public Component
	{
	public:
		virtual float getDensity() { return density; }
		virtual void setDensity(float density_) { density = density; }
		virtual float getFriction() { return friction; }
		virtual void setFriction(float friction_) { friction = friction_; }
		virtual float getScale() { return scale; };
		virtual void setScale(float scale_) { scale = scale; };
	protected:
		Collider2D(GameObject* gameObject) : Component(gameObject), shape(nullptr), density(1), friction(0.1f) { }
		
		b2Shape* shape;

		float scale;
		float density;
		float friction;

		friend class GameObject;
		friend class PhysicsBody2D;
	};

	
}
