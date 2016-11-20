#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>

class Transform : public Component {
public:
	
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	void setParent(Transform *gameObject);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	Transform* getParent();

	glm::mat4 localTransform();
	glm::mat4 globalTransform();
protected:
	Transform(GameObject *gameObject);
	friend class GameObject;
	friend class Rendering;
	friend class ParticleEmitter;


	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Transform* parent;
};