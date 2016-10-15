#include "PhysicsBody.hpp"

PhysicsBody::~PhysicsBody() {
	auto vec = &Physics::instance->bodies;
	vec->erase(remove(vec->begin(), vec->end(), this), vec->end());
}

PhysicsBody::PhysicsBody(GameObject* gameObject) : Component(gameObject) {
	Physics::instance->bodies.push_back(this);
}