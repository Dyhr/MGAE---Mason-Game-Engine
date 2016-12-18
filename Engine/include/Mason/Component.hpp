#pragma once
#include <memory>

namespace Mason {

	class GameObject;
	/** @class Component super class for all components. Has a shared pointer to its gameobject
	*/
	class Component {
	public:
		/** @brief Destructor.
		*/
		virtual ~Component();
		/** @brief Returns a shared pointer to the gameobject of the component.
		*/
		std::shared_ptr<GameObject> getGameObject();
	protected:
		/** @brief Constructor.
		*/
		Component(std::shared_ptr<GameObject> gameObject);
		std::shared_ptr<GameObject> gameObject; ///< shared pointer to gameobject

		friend class GameObject;
	};
}
