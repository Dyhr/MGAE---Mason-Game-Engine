#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>

namespace Mason {
	class Transform : public Component {
	public:

		virtual void setPosition(glm::vec3 position);
		virtual void setRotation(float rotation);
		virtual void setScale(float scale);
		virtual void setParent(Transform *gameObject);

		virtual glm::vec3 getPosition();
		virtual float getRotation();
		virtual float getScale();
		virtual Transform* getParent();

		glm::mat4 localTransform() const;
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