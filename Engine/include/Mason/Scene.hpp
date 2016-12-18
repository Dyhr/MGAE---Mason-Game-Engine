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
		/** @brief constructor
		*/
		Scene();
		static std::shared_ptr<GameObject> Instantiate(std::string name);
		static void Destroy(std::shared_ptr<GameObject> ptr);
		static void Destroy(GameObject* ptr);

		static std::vector<std::shared_ptr<GameObject>> GetByName(std::string name);

		/** @brief Add game object
		*/
		
		std::shared_ptr<GameObject> addGameObject(std::string name);

		/** @brief Load game object from decriptor
		*/
		
		std::shared_ptr<GameObject> loadGameObject(GameObjectDescriptor desc);

		/** @brief Setup a parent-child relationship between gameobjects
		*/
		
		void setParentRelationship(int childId, int parentId);

		/** @brief Remove game object
		*/
		
		bool removeGameObject(std::shared_ptr<GameObject> ptr);

		/** @brief Get number of game objects
		*/
		
		int getSize();

		/** @brief Get game object by index
		*/
		
		std::shared_ptr<GameObject> getGameObject(int index);

		/** @brief Get all game objects
		*/
		
		std::vector<std::shared_ptr<GameObject>> getGameObjects();

		/** @brief Returns all components of type C
		* @return std::vector<C*>
		*/
		template<typename C>
		std::vector<C*> getAllComponent();

	private:
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::map<std::string, std::shared_ptr<Sprite>> sprites;
		std::map<int, std::shared_ptr<GameObject>> gameObjectIds;
		std::map<std::string, std::vector<std::shared_ptr<GameObject>>> gameObjectNames;

		std::vector<std::shared_ptr<GameObject>> destroyList;

		std::string templatepath;
		std::string imagepath;
		std::string soundpath;

		static Scene* activeInstance;
		
		//Load components from descriptors
		/** @brief loads components of this kind from its descriptor
		*/
		void loadCameraComponent(GameObjectDescriptor goDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadParticleComponent(ParticleDescriptor particleDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadSpriteComponent(SpriteDescriptor spriteDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadPhysicsBodyComponent(PhysicsBodyDescriptor physicsDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadBoxColliderComponent(BoxColliderDescriptor boxColliderDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadCircleColliderComponenet(CircleColliderDescriptor circleColliderDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadTransformComponent(TransformDescriptor transformDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadAudioComponent(AudioDescriptor audioDesc, std::shared_ptr<GameObject> go);

		/** @brief loads components of this kind from its descriptor
		*/
		void loadScriptComponent(ScriptDescriptor scriptDesc, std::shared_ptr<GameObject> go);


		friend class Engine;
	};

	/** @brief gets all the components of the scene
	* @return std::vector<C*>
	*/
	//function templates has to be defined in header files
	template<typename C>
	std::vector<C*> Scene::getAllComponent() {
		std::vector<C*> res;
		for (auto& go : gameObjects) {
			auto c = go->getComponent<C>();
			if (c != nullptr) {
				res.push_back(c);
			}
		}
		return res;
	}
}
