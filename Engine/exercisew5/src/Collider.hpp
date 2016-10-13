#pragma once
#include "Component.hpp"

class Collider2D : public Component {
public:
protected:
	Collider2D(GameObject* gameObject) : Component(gameObject) {}
};