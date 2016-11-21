#pragma once

#include "Component.hpp"
#include <memory>
#include "Sprite.h"

namespace Mason {

	class Transform;

	class SpriteRenderer : public Component {
	public:
		void draw();

		std::shared_ptr<Sprite> sprite;

	protected:
		SpriteRenderer(GameObject *gameObject);

		std::shared_ptr<Transform> transform;

		friend class GameObject;
	};
}
