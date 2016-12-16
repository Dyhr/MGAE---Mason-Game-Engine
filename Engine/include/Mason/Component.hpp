#pragma once
#include <memory>

namespace Mason {

	class GameObject;

	class Component {
	public:
		virtual ~Component();
		std::shared_ptr<GameObject> getGameObject();
	protected:
		Component(std::shared_ptr<GameObject> gameObject);
		std::shared_ptr<GameObject> gameObject;

		friend class GameObject;
	};
}
