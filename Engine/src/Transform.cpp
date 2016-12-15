#include "Mason/Transform.h"

#include "Mason/GameObject.hpp"
#include "Mason/PhysicsBody2D.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Mason;

Transform::Transform(GameObject *gameObject):Component(gameObject) {
	this->position = glm::vec3(0, 0, 0);
	this->rotation = glm::vec3(0, 0, 0);
	this->scale = glm::vec3(1, 1, 1);
	this->parent = nullptr;
}

void Transform::transformize()
{
	auto translateMat = translate(glm::mat4(1), position);
	auto rotateMat = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
	auto scaleMat = glm::scale(glm::mat4(1), scale);
	matrix = translateMat * rotateMat * scaleMat;
}

void Transform::setPosition(glm::vec3 position) {
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->body->SetTransform(b2Vec2(position.x, position.y), body->body->GetAngle());
	this->position = position;
	transformize();
}

void Transform::setRotation(glm::vec3 rotation) {
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->body->SetTransform(body->body->GetWorldCenter(), rotation.z);
	this->rotation = rotation;
	transformize();
}


void Transform::setScale(glm::vec3 scale) {
	this->scale = scale;
	transformize();
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
	return matrix;

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