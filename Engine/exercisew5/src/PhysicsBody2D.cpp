#include "PhysicsBody2D.hpp"

PhysicsBody2D::~PhysicsBody2D() {
}

PhysicsBody2D::PhysicsBody2D(GameObject* gameObject) : Component(gameObject) {
	b2BodyDef bd;
	body = Physics::instance->world->CreateBody(&bd);
}