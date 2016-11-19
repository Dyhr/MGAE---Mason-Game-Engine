#include "Mason/GameObject.hpp"

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
