#pragma once

#include <string>
#include <vector>
#include "GameObject.hpp"
#include <map>
#include "Sprite.h"
#include "SceneParser.hpp"

namespace Mason {
	class Scene {
	public:
		Scene();
		static std::shared_ptr<GameObject> Instantiate(GameObjectDescriptor desc);
		static void Destroy(std::shared_ptr<GameObject> ptr);
		// Add game object
		std::shared_ptr<GameObject> addGameObject(std::string name);

		//Load game object from decriptor
		std::shared_ptr<GameObject> loadGameObject(GameObjectDescriptor desc);

		//Setup a parent-child relationship between gameobjects
		void setParentRelationship(int childId, int parentId);

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
		std::map<std::string, std::shared_ptr<Sprite>> sprites;
		std::map<int, std::shared_ptr<GameObject>> map_gameObjects;

		static Scene* activeInstance;
		
		//Load components from descriptors
		void loadCameraComponent(GameObjectDescriptor goDesc, std::shared_ptr<GameObject> go);
		void loadParticleComponent(ParticleDescriptor particleDesc, std::shared_ptr<GameObject> go);
		void loadSpriteComponent(SpriteDescriptor spriteDesc, std::shared_ptr<GameObject> go);
		void loadPhysicsBodyComponent(PhysicsBodyDescriptor physicsDesc, std::shared_ptr<GameObject> go);
		void loadBoxColliderComponent(BoxColliderDescriptor boxColliderDesc, std::shared_ptr<GameObject> go);
		void loadCircleColliderComponenet(CircleColliderDescriptor circleColliderDesc, std::shared_ptr<GameObject> go);
		void loadTransformComponent(TransformDescriptor transformDesc, std::shared_ptr<GameObject> go);
		void loadAudioComponent(AudioDescriptor audioDesc, std::shared_ptr<GameObject> go);
		void loadScriptComponent(ScriptDescriptor scriptDesc, std::shared_ptr<GameObject> go);


		friend class Engine;
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
