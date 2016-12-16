#pragma once

#include "Component.hpp"
#include <memory>
#include "Sprite.h"

namespace Mason {
	/** @class SpriteRenderer
	* @brief calls the draw() method of every Sprite.
	*
	* @fn draw()
	* @brief calls the draw() method on a specific Sprite providing its global transform (= position in the game world). @see Transform component
	*/
	class Transform;

	class SpriteRenderer : public Component {
	public:
		void draw();

		std::shared_ptr<Sprite> sprite; ///< Pointer to the @see Sprite that is going to be rendered.

	protected:
		SpriteRenderer(std::shared_ptr<GameObject> gameObject);

		std::shared_ptr<Transform> transform;

		friend class GameObject;
	};
}
