#pragma once

#include <string>
#include <vector>
#include "GameObject.hpp"
#include <map>
#include "Sprite.h"
#include "SceneParser.hpp"

namespace Mason {
	/** @class Scene Holds all GameObjects, sprites, paths to images, templates, and sounds
	*/
	class Scene {
	public:
		/** @brief Constructor
		*/
		Scene();
		/** @brief Instantiate a gameobject
		* @param name template name
		*/
		static std::shared_ptr<GameObject> Instantiate(std::string name);
		/** @brief Destroy a gameobject
		* @param ptr shared pointer to gameobject
		*/
		static void Destroy(std::shared_ptr<GameObject> ptr);
		/** @brief Destroy a gameobject
		* @param ptr pointer to gameobject
		*/
		static void Destroy(GameObject* ptr);
		/** @brief Get a shared pointer to a game object
		* @param name name of game object
		*/
		static std::vector<std::shared_ptr<GameObject>> GetByName(std::string name);
		
		/** @brief Add a gameobject to the scene. Get a shared pointer to it in return.
		* @param name name of game object
		*/
		std::shared_ptr<GameObject> addGameObject(std::string name);

		/** @brief Load a gameobject. Returns a shared pointer to it. Used by Instantiate.
		* @param desc descriptor object of gameobject
		*/
		std::shared_ptr<GameObject> loadGameObject(GameObjectDescriptor desc);

		/** @brief Sets up a parent-child relationship between two gameobject.
		* @param childId unique id of child game object
		* @param parentId unique id of parent game object
		*/
		void setParentRelationship(int childId, int parentId);

		/** @brief Remove a game object from the scene.
		* @param ptr shared pointer to the gameobject that is to be removed.
		*/
		bool removeGameObject(std::shared_ptr<GameObject> ptr);

		/** @brief Get the number of game objects in the scene		
		*/
		int getSize();

		/** @brief Get a game object by index
		* @param index index of gameobject
		*/
		std::shared_ptr<GameObject> getGameObject(int index);

		/** @brief Get all game objects in scene
		*/
		std::vector<std::shared_ptr<GameObject>> getGameObjects();

		/** @brief Returns all components of type C
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
		friend class Scene;
	};


	/** @brief Get all components of type C
	*/
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
