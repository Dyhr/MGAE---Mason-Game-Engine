#pragma once
#include "Component.hpp"
#include "Physics.hpp"

class Collider : public Component {
public:
protected:
	Collider(GameObject* gameObject) : Component(gameObject) { }
};
