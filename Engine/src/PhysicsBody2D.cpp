#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Collider2D.hpp"
#include "Mason/GameObject.hpp"

#include <algorithm>

using namespace Mason;

PhysicsBody2D::~PhysicsBody2D() {
	auto vec = &Physics::instance->bodies;
	vec->erase(remove(vec->begin(), vec->end(), this), vec->end());
}

PhysicsBody2D::PhysicsBody2D(GameObject* gameObject) : Component(gameObject) {
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	body = Physics::instance->world.CreateBody(&bd);
	Physics::instance->bodies.push_back(this);
}

void PhysicsBody2D::UpdateFixtures() {
	auto fixture = body->GetFixtureList();
	while (fixture) {
		body->DestroyFixture(fixture);
		fixture = fixture->GetNext();
	}

	auto colliders = getGameObject()->getComponents<Collider2D>();
	for (auto collider : colliders) {
		b2FixtureDef fd;
		fd.shape = collider->shape;
		fd.density = collider->density;
		fd.friction = collider->friction;
		body->CreateFixture(&fd)->SetUserData(static_cast<void*>(gameObject)); //our body is a container for the body we get from box2D
	}
}