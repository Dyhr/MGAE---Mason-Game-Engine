#pragma once

#include "Mason/Transform.h"
#include <memory>
#include <SRE/Camera.hpp>
#include <glm/glm.hpp>

class Camera : protected Transform {
public:

	void setPerspectiveProjection(float fieldOfView, float viewPortWidth, float viewPortHeight, float nearClip, float farClip) const;
	void lookAt(glm::vec3 at, glm::vec3 up) const;

	~Camera();

protected:
	Camera(GameObject *gameObject);

	SRE::Camera* cam;

	friend class GameObject;
	friend class Engine;
};
