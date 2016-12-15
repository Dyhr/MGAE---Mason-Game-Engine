#include "Mason/CircleCollider2D.h"

#include "Mason/GameObject.hpp"
#include "Mason/PhysicsBody2D.hpp"

using namespace Mason;

void CircleCollider2D::setCenter(float x, float y)
{
	//center = b2Vec2(x, y);
	circleShape.m_p.Set(x,y);
	
}
void CircleCollider2D::setScale(float scale) {
	Collider2D::setScale(scale);

	setSize(scale);
	auto body = gameObject->getComponent<PhysicsBody2D>();
	if (body != nullptr)
		body->UpdateFixtures();
}
void CircleCollider2D::setSize(float rad)
{
	circleShape.m_radius = rad;
}

CircleCollider2D::CircleCollider2D(GameObject* gameObject) : Collider2D(gameObject)
{
	shape = &circleShape; //fixture which uses this shape
	setCenter(0, 0);
	setSize(1);
}
