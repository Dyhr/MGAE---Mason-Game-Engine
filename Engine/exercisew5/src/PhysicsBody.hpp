#pragma once

#include "Component.hpp"
#include "Physics.hpp"

class PhysicsBody : public Component {
public:
	~PhysicsBody();

protected:
	PhysicsBody(GameObject* gameObject);
	friend class GameObject;
};
