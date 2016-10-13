#pragma once

#include "Component.hpp"
#include "Physics.hpp"
#include "Box2D/Box2D.h"

class PhysicsBody : public Component {
public:
	~PhysicsBody();

protected:
	PhysicsBody(GameObject* gameObject);
	friend class GameObject;
};
