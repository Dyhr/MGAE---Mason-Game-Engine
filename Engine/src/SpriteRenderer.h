#pragma once

#include "Component.hpp"
#include <memory>
#include "Sprite.h"

class Transform;
class GameObject;

class SpriteRenderer : public Component {
public:
	void draw();

	std::shared_ptr<Sprite> sprite;

protected:
	SpriteRenderer(GameObject *gameObject);

	std::shared_ptr<Transform> transform;

	friend class GameObject;
};
