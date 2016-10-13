#pragma once

#include "Component.hpp"
#include "Physics.hpp"
//#include "Box2D/Box2D.h"

class PhysicsBody2D : public Component {
public:
	~PhysicsBody2D();
	//b2Body* body;

protected:
	PhysicsBody2D(GameObject* gameObject);
	friend class GameObject;
};
