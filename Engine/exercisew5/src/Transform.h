#pragma once
#include "Component.hpp"
#include "glm/glm.hpp"
#pragma once
#include "GameObject.hpp"
#include "Rendering.h"

class Transform : public Component {
public:
	
	//glm::vec3 position;glm::vec3 rotation;glm::vec3 scale;
	void setPosition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	void setParent(GameObject *gameObject);

	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();
	GameObject getParent();

protected:
	Transform(GameObject *gameObject);
	friend class GameObject;
	friend class Rendering;
	glm::mat4 localTransform();
	glm::mat4 globalTransform();

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	GameObject parent;
};