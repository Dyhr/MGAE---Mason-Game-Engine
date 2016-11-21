#include <Mason/Camera.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <iostream>


using namespace Mason;

Camera::Camera(GameObject* gameObject) : Transform(gameObject)
{
	cam = new SRE::Camera();
}

void Camera::transformize()
{
	Transform::transformize();
	//cam->setViewTransform(matrix);
}

Camera::~Camera()
{
	delete cam;
}

void Camera::setPerspectiveProjection(float fieldOfView, float viewPortWidth, float viewPortHeight, float nearClip, float farClip) const
{
	cam->setPerspectiveProjection(fieldOfView, viewPortWidth, viewPortHeight, nearClip, farClip);
}

void Camera::lookAt(glm::vec3 at, glm::vec3 up) const
{
	cam->lookAt(position, at, up);
}
