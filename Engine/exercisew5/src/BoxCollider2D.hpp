#pragma once
#include "Component.hpp"
#include <Box2D/Box2D.h>
#include "Collider2D.hpp"

class BoxCollider2D : public Collider2D
{
public:
	void setCenter(float x, float y);
	void setSize(float width, float height);
protected:
	BoxCollider2D(GameObject* gameObject);
private:
	b2PolygonShape polyShape;
	b2Vec2 center;
	b2Vec2 size;
};
