//
// Created by Morten Nobel-Jørgensen on 07/10/16.
//

#include "Scene.hpp"

using namespace std;

Scene* Scene::instance = nullptr;

Scene* Scene::getInstance()
{
	if (instance == nullptr) instance = new Scene();
	return instance;
}

std::shared_ptr<GameObject> Scene::addGameObject(std::string name) {
    GameObject * go = new GameObject(name);
    auto res = shared_ptr<GameObject>(go);
	this->gameObjects.push_back(res);
    return res;
}

bool Scene::removeGameObject(std::shared_ptr<GameObject> ptr) {
    for (auto iter = this->gameObjects.begin();iter != this->gameObjects.end(); iter++){
        if (*iter == ptr){
			this->gameObjects.erase(iter);
            return true;
        }
    }
    // not found
    return false;
}

int Scene::getSize() {
    return (int) this->gameObjects.size();
}

std::shared_ptr<GameObject> Scene::getGameObject(int index) {
    return this->gameObjects.at(index);
}

std::vector<std::shared_ptr<GameObject>> Scene::getGameObjects() {
	return this->gameObjects;
		
}
