
//
// Created by Morten Nobel-Jørgensen on 07/10/16.
//

#include "GameObject.hpp"
//everytime we create a gameobject we should add its Transform

GameObject::GameObject(std::string name_):name(name_) //why???
{
}

GameObject::~GameObject() {

}

std::string GameObject::getName() {
    return name;
}

std::shared_ptr<Transform> GameObject::getTransform(){
	return this->transform;
}
void GameObject::setTransform(std::shared_ptr<Transform> tr) {
	this->transform = tr;
}

bool GameObject::removeComponent(std::shared_ptr<Component> ptr) {
    for (auto iter = components.begin();iter != components.end(); iter++){
        if (*iter == ptr){
            components.erase(iter);
            ptr.reset();
            return true;
        }
    }
    return false;
}
