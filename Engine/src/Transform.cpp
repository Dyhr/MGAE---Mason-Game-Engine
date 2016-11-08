#include "Transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject *gameObject):Component(gameObject) {
	this->position = glm::vec3(0, 0, 0);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(0, 0, 0);
	this->parent = nullptr;
}

void Transform::setPosition(glm::vec3 position) {
	this->position = position;
}

void Transform::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}


void Transform::setScale(glm::vec3 scale) {
	this->scale = scale;
}

void Transform::setParent(Transform *parent) {
	this->parent = parent;
}
glm::vec3 Transform::getPosition() {
	return this->position;
}

glm::vec3 Transform::getRotation() {
	return this->rotation;
}
glm::vec3 Transform::getScale() {
	return this->scale;
}
Transform* Transform::getParent() {
	return this->parent;
}

glm::mat4 Transform::localTransform() {
	auto translateMat = glm::translate(glm::mat4(1), position);
	auto rotateMat = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
	auto scaleMat = glm::scale(glm::mat4(1), scale);
	auto transform = translateMat * rotateMat * scaleMat;

	return transform;

}

glm::mat4 Transform::globalTransform() {
	glm::mat4 transform = localTransform();
	Transform* parent = this->getParent();
	if (parent) {
		auto parentTransform = parent->globalTransform();
		transform = parentTransform * transform;
	}
	return transform;
}