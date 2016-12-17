#include "Mason/PhysicsBody2D.hpp"
#include "Mason/Collider2D.hpp"
#include "Mason/GameObject.hpp"

#include <algorithm>

#include <Box2D/Box2D.h>

using namespace Mason;

PhysicsBody2D::~PhysicsBody2D() {
	auto vec = &Physics::instance->bodies;
	vec->erase(remove(vec->begin(), vec->end(), this), vec->end());
}

PhysicsBody2D::PhysicsBody2D(std::shared_ptr<GameObject> gameObject) : Component(gameObject) {
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	body = Physics::instance->world->CreateBody(&bd);
	Physics::instance->bodies.push_back(this);
}

void PhysicsBody2D::UpdateFixtures() {
	for(auto fixture : fixtures) {
		body->DestroyFixture(fixture);
	}
	fixtures.clear();

	auto colliders = getGameObject()->getComponents<Collider2D>();
	for (auto collider : colliders) {
		b2FixtureDef fd;
		fd.shape = collider->shape;
		fd.density = collider->density;
		fd.friction = collider->friction;
		auto fixture = body->CreateFixture(&fd);
		fixture->SetUserData(static_cast<void*>(gameObject.get())); //our body is a container for the body we get from box2D
		fixtures.push_back(fixture);
	}
}