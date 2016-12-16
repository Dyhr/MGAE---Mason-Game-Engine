#pragma once

#include "Component.hpp"
#include "Physics.hpp"

namespace Mason {

	/** @class PhysicsBody2D
	* @brief creates a body in the physics world, so they affect the game object that this component is attached to.
	*/
	class PhysicsBody2D : public Component {
	public:
		/** @brief destructor of the physics body.
		* removes the body from the list of bodies hold by the world.
		*/
		~PhysicsBody2D();

		/** @brief resizes the physics body if necessary
		* updates the dimension of the physics body (specifically its fixture) if the transform of the gameobject related is scaled.
		* for this, the method destroys all the fixtures related to the game object and creates new ones according to the components and values stored in the game object.
		*/
		void UpdateFixtures();
		b2Body* body; ///< rigid body created in the Physics world

	protected:
		PhysicsBody2D(std::shared_ptr<GameObject> gameObject);

		std::vector<b2Fixture*> fixtures;

		friend class GameObject;
	};
}
