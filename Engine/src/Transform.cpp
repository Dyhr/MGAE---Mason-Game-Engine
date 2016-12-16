#include "Mason/Transform.h"

#include "Mason/GameObject.hpp"
#include "Mason/PhysicsBody2D.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Mason;

Transform::Transform(GameObject *gameObject):Component(gameObject) {
	this->position = glm::vec3(0, 0, 0);
	this->rotation = 0;
	this->scale = 1;
	this->parent = nullptr;
}

void Transform::transformize()
{
	auto translateMat = translate(glm::mat4(1), position);
	auto rotateMat = glm::eulerAngleYXZ(0.0f, 0.0f, glm::radians(rotation));
	auto scaleMat = glm::scale(glm::mat4(1), glm::vec3(scale, scale, 1));
	matrix = translateMat * rotateMat * scaleMat;
}

void Transform::setPosition(glm::vec3 position) {
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->body->SetTransform(b2Vec2(position.x / Physics::instance->phScale, position.y / Physics::instance->phScale), body->body->GetAngle());
	this->position = position;
	transformize();
}

void Transform::setRotation(float rotation) {
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->body->SetTransform(body->body->GetWorldCenter(), rotation);
	this->rotation = rotation;
	transformize();
}


void Transform::setScale(float scale) {
	this->scale = scale;
	transformize();
}

void Transform::setParent(Transform *parent) {
	this->parent = parent;
}
glm::vec3 Transform::getPosition() {
	return this->position;
}

float Transform::getRotation() {
	return this->rotation;
}
float Transform::getScale() {
	return this->scale;
}
Transform* Transform::getParent() {
	return this->parent;
}

glm::mat4 Transform::localTransform() const
{
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