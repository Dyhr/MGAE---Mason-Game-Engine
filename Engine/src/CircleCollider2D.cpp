#include "Mason/CircleCollider2D.h"

using namespace Mason;

void CircleCollider2D::setCenter(float x, float y)
{
	//center = b2Vec2(x, y);
	circleShape.m_p.Set(x,y);
	
}
b2Vec2 CircleCollider2D::GetScale() {
	return (b2Vec2(1.0, 1.0));
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
