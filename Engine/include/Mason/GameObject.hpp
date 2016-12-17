#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Transform.h"


namespace Mason {

	class Scene;
	class Script;

	class GameObject {
	public:
		~GameObject();
		GameObject(std::string name);

		std::string getName() const;
		void setName(std::string nm);

		template<typename C>
		C* addComponent();

		bool removeComponent(Component* ptr);

		Script* addScript(std::string name);

		template<typename C>
		C* getComponent();
		template<typename C>
		std::vector<C*> getComponents();

		Transform* getTransform() const;

	private:
		std::vector<Component*> components;

		bool destroyed = false;
		std::shared_ptr<GameObject>* me;
		Transform* transform;
		std::string name;

		friend class Scene;
		friend class CollisionListener;
	};

	// function templates has to defined in header files
	template<typename C>
	C* GameObject::addComponent() {
		C * c = new C(*me);
		components.push_back(c);
		return c;
	}

	template<typename C>
	C* GameObject::getComponent() {
		for (auto c : components) {
			auto castPtr = dynamic_cast<C*>(c);
			if (castPtr != nullptr)
				return castPtr;
		}
		// not found
		return nullptr;
	}
	template<typename C>
	std::vector<C*> GameObject::getComponents() {
		std::vector<C*> result;
		for (auto c : components) {
			auto castPtr = dynamic_cast<C*>(c);
			if (castPtr != nullptr)
				result.push_back(castPtr);
		}
		return result;
	}
}
