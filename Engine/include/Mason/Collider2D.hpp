#pragma once
#include "Component.hpp"
#include "Physics.hpp"

class b2Shape;

namespace Mason {
	/** @class Collider2D
	* @brief creates a collider in the physics world, so they affect the game object that this component is attached to.
	* it is a virtual class, as its methods are expected to be override by specific kinds of colliders: BoxCollider2D and CircleCollider2D
	*/
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

		/** @brief Constructor of Collider2D
		* defines the shape, density and friction of the fixtures of the bodies in the world ( PhysicsBody2D ).
		*/
		Collider2D(std::shared_ptr<GameObject> gameObject) : Component(gameObject), shape(nullptr), density(1), friction(0.1f), scale(1) { }
		
		b2Shape* shape; ///< in the world, shapes are created automatically when a b2Fixture is created (in a PhysicsBody2D ).

		float scale;
		float density;
		float friction;

		friend class GameObject;
		friend class PhysicsBody2D;
	};

	
}
