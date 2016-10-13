#include "BoxCollider2D.hpp"

void BoxCollider2D::setCenter(float x, float y)
{
	//center = b2Vec2(x, y);
}

void BoxCollider2D::setSize(float width, float height)
{
	//size = b2Vec2(width, height);
}

BoxCollider2D::BoxCollider2D(GameObject* gameObject): Collider2D(gameObject)
{
	//shape = &polyShape;
}
