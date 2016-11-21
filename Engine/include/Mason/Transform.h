#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>

namespace Mason {
	class Transform : public Component {
	public:

		virtual void setPosition(glm::vec3 position);
		virtual void setRotation(glm::vec3 rotation);
		virtual void setScale(glm::vec3 scale);
		void setParent(Transform *gameObject);

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();
		Transform* getParent();

		glm::mat4 localTransform();
		glm::mat4 globalTransform();
	protected:
		Transform(GameObject *gameObject);

		virtual void transformize();

		glm::mat4 matrix;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		Transform* parent;


		friend class GameObject;
		friend class Rendering;
		friend class ParticleEmitter;
	};
}