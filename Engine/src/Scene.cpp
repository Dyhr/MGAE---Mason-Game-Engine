#include "Mason/Scene.hpp"

using namespace std;
using namespace Mason;

shared_ptr<GameObject> Scene::addGameObject(string name) {
    GameObject * go = new GameObject(name);
    auto res = shared_ptr<GameObject>(go);
	this->gameObjects.push_back(res);
    return res;
}

bool Scene::removeGameObject(shared_ptr<GameObject> ptr) {
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

shared_ptr<GameObject> Scene::getGameObject(int index) {
    return this->gameObjects.at(index);
}

vector<shared_ptr<GameObject>> Scene::getGameObjects() {
	return this->gameObjects;
}
