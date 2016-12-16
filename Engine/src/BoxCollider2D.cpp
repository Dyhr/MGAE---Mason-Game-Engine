#include "Mason/BoxCollider2D.hpp"


using namespace Mason;

void BoxCollider2D::setCenter(float x, float y)
{
	center = b2Vec2(x / Physics::instance->phScale, y / Physics::instance->phScale);
	polyShape.SetAsBox(size.x, size.y, center, 0);
}

void BoxCollider2D::setSize(float width, float height)
{
	size = b2Vec2((width / 2) / Physics::instance->phScale, (height / 2) / Physics::instance->phScale);
	polyShape.SetAsBox(size.x, size.y, center, 0);
}

BoxCollider2D::BoxCollider2D(GameObject* gameObject) : Collider2D(gameObject)
{
	shape = &polyShape;
	setCenter(0, 0);
	setSize(1, 1);
}