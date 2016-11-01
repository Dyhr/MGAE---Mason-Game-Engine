#include "Component.hpp"
#pragma once
#include "glm/glm.hpp"

class Transform : public Component {
public:
	glm::mat4 localTransform();
	glm::mat4 globalTransform();

protected:
	Transform(GameObject *gameObject);
	friend class GameObject;
};