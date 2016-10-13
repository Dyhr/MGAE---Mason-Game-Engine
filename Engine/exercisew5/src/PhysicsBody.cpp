#include "PhysicsBody.hpp"

PhysicsBody::~PhysicsBody() {
}

PhysicsBody::PhysicsBody(GameObject* gameObject) : Component(gameObject) {
}