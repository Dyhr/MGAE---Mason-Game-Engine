
//
// Created by Morten Nobel-Jørgensen on 07/10/16.
//

#include "GameObject.hpp"

GameObject::GameObject(std::string name_)
:name(name_)
{
}

GameObject::~GameObject() {

}


std::string GameObject::getName() {
    return name;
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
