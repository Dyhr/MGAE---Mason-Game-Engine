#include "Mason/Scene.hpp"

using namespace std;

std::shared_ptr<GameObject> Scene::addGameObject(std::string name) {
    GameObject * go = new GameObject(name);
    auto res = shared_ptr<GameObject>(go);
    gameObjects.push_back(res);
    return res;
}

bool Scene::removeGameObject(std::shared_ptr<GameObject> ptr) {
    for (auto iter = gameObjects.begin();iter != gameObjects.end(); iter++){
        if (*iter == ptr){
            gameObjects.erase(iter);
            return true;
        }
    }
    // not found
    return false;
}

int Scene::getSize() {
    return (int) gameObjects.size();
}

std::shared_ptr<GameObject> Scene::getGameObject(int index) {
    return gameObjects.at(index);
}
