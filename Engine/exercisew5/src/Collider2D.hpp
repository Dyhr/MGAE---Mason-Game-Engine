#pragma once
#include "Component.hpp"
//#include <Box2D/Box2D.h>

class Collider2D : public Component
{
public:
	//b2Shape* shape;
protected:
	Collider2D(GameObject* gameObject) : Component(gameObject)/*, shape(nullptr)*/ {}
};
