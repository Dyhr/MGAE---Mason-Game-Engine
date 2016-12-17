#include "Mason/BoxCollider2D.hpp"

#include "Box2D/Box2D.h"

using namespace Mason;
/** @class BoxCollider2D
* @brief creates a Collider2D with rectangular-shape properties.
* overrides the virtual class Collider2D
*/

void BoxCollider2D::setCenter(float x, float y) const
{
	center->x = x / Physics::instance->phScale;
	center->y = y / Physics::instance->phScale;
	polyShape->SetAsBox(size->x, size->y, *center, 0);
}

void BoxCollider2D::setSize(float width, float height) const
{
	size->x = (width / 2) / Physics::instance->phScale;
	size->y = (height / 2) / Physics::instance->phScale;
	polyShape->SetAsBox(size->x, size->y, *center, 0);
}

BoxCollider2D::BoxCollider2D(std::shared_ptr<GameObject> gameObject) : Collider2D(gameObject)
{
	center = new b2Vec2();
	size = new b2Vec2();
	polyShape = new b2PolygonShape();
	shape = polyShape;
	setCenter(0, 0);
	setSize(1, 1);
}

BoxCollider2D::~BoxCollider2D()
{
	delete center;
	delete size;
	delete shape;
}
