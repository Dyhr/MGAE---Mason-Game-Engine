#pragma once

#include <string>
#include <vector>
#include "GameObject.hpp"

namespace Mason {
	class Scene {
	public:

		// Add game object
		std::shared_ptr<GameObject> addGameObject(std::string name);

		// Remove game object
		bool removeGameObject(std::shared_ptr<GameObject> ptr);

		// Get number of game objects
		int getSize();

		// Get game object by index
		std::shared_ptr<GameObject> getGameObject(int index);

		//Get all game objects
		std::vector<std::shared_ptr<GameObject>> getGameObjects();

		// Returns all components of type C
		template<typename C>
		std::vector<std::shared_ptr<C>> getAllComponent();

	private:
		std::vector<std::shared_ptr<GameObject>> gameObjects;
	};

	// function templates has to defined in header files
	template<typename C>
	std::vector<std::shared_ptr<C>> Scene::getAllComponent() {
		std::vector<std::shared_ptr<C>> res;
		for (auto& go : gameObjects) {
			std::shared_ptr<C> c = go->getComponent<C>();
			if (c.get() != nullptr) {
				res.push_back(c);
			}
		}
		return res;
	}

}
