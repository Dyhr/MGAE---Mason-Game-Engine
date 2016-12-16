#include <Mason/Camera.hpp>
#include <SRE/SimpleRenderEngine.hpp>
#include <iostream>
#include "Mason/Config.hpp"


using namespace Mason;

Camera::Camera(GameObject* gameObject) : Transform(gameObject)
{
	cam = new SRE::Camera();
}

void Camera::transformize()
{
	Transform::transformize();
	cam->setWindowCoordinates(
		int(*Config::getInt("window-width") * (viewportMax.x - viewportMin.x)),
		int(*Config::getInt("window-height") * (viewportMax.y - viewportMin.y)));

	cam->setViewTransform(matrix);
}

glm::vec3 Camera::offset() const
{
	return glm::vec3(
		(viewportMax.x - viewportMin.x) * (*Config::getInt("window-width")) * 0.5f,
		(viewportMax.y - viewportMin.y) * (*Config::getInt("window-height")) * 0.5f,
		0);
}

void Camera::setScale(float scale)
{
	Transform::setScale(1 / scale);
}

void Camera::setPosition(glm::vec3 position)
{
	Transform::setPosition(-position + offset());
}

float Camera::getScale()
{
	return 1 / scale;
}

glm::vec3 Camera::getPosition()
{
	return -position + offset();
}

glm::vec2 Camera::getViewportMin() const
{
	return viewportMin;
}

void Camera::setViewportMin(glm::vec2 viewport_min)
{
	viewportMin = viewport_min;
	cam->setViewport(
		int(viewportMin.x * *Config::getInt("window-width")),
		int(viewportMin.y * *Config::getInt("window-height")),
		int((viewportMax.x - viewportMin.x) * *Config::getInt("window-width")),
		int((viewportMax.y - viewportMin.y) * *Config::getInt("window-height")));
	transformize();
}

glm::vec2 Camera::getViewportMax() const
{
	return viewportMax;
}

void Camera::setViewportMax(glm::vec2 viewport_max)
{
	viewportMax = viewport_max;
	cam->setViewport(
		int(viewportMin.x * *Config::getInt("window-width")),
		int(viewportMin.y * *Config::getInt("window-height")),
		int((viewportMax.x - viewportMin.x) * *Config::getInt("window-width")),
		int((viewportMax.y - viewportMin.y) * *Config::getInt("window-height")));
	transformize();
}

Camera::~Camera()
{
	delete cam;
}
