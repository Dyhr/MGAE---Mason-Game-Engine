#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>

namespace Mason {
	/** @class Transform 
	* @brief used to store and manipulate the position, rotation and scale of the game object
	* In 2D physics there are 3 DOF (degrees of freedom) to move the bodies around: positional (x, y) and rotation around the ‘z axis’. We use the same logic for every game object in the game.
	*/
	class Transform : public Component {
	public:
		/** @brief sets position in 2D
		* sets the position according by the scale provided
		* @param position Vector 3. In 2D we don't need the z coordenate: position.z=0
		*/
		virtual void setPosition(glm::vec3 position);

		/** @brief rotates the GameObject around the z axis
		* sets the position according by the scale provided
		* @param rotation. It is a float. In 2D, bodies can only rotate on the z axis, so we don't need to use a Vector3.
		*/
		virtual void setRotation(float rotation);

		/** @brief scales the GameObject. Same scale in x and y.
		* as we don't need to scale differently in x and y any element in our game, we use the same value to scale in both axis.
		* @param scale. It is a float used to scale in x and y.
		*/
		virtual void setScale(float scale);

		/** @brief sets the parent, if indicated.
		* @param gameObject Every Transform can have a parent, which allows to apply position, rotation and scale hierarchically.
		*/
		virtual void setParent(Transform *gameObject);
		/** @brief gets the position of the transform
		* @return Vector3 (x,y,z)
		*/
		virtual glm::vec3 getPosition();

		/** @brief gets the rotation of the transform
		* @return float rotation on the z axis
		*/
		virtual float getRotation();

		/** @brief gets the scale of the transform
		* @return float scale in x and y
		*/
		virtual float getScale();

		/** @brief gets the parent of the transform
		* @return a pointer to the parent's Transform (Transform*)
		*/
		virtual Transform* getParent();

		/** @brief gets the matrix of the transform
		* @return Mat4 (x,y,z,w)
		*/
		glm::mat4 localTransform() const;

		/** @brief gets the matrix of the transform getting the global coordinates from a parent (inheritance)
		* @return Mat4 (x,y,z,w)
		*/
		glm::mat4 globalTransform();
	protected:
		Transform(std::shared_ptr<GameObject> gameObject);

		virtual void transformize();

		glm::mat4 matrix;
		glm::vec3 position;
		float rotation;
		float scale;
		Transform* parent;


		friend class GameObject;
		friend class Rendering;
		friend class ParticleEmitter;
		friend class Physics;
	};
}