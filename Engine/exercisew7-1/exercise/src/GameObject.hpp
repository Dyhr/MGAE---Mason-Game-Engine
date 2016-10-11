#pragma once

#include <string>
#include <vector>
#include "Component.hpp"

// forward declaration
class Scene;

class GameObject {
public:
    ~GameObject();

    std::string getName();
    template<typename C>
    std::shared_ptr<C> addComponent();

    bool removeComponent(std::shared_ptr<Component> ptr);


    template<typename C>
    std::shared_ptr<C> getComponent();

private:
    std::vector<std::shared_ptr<Component>> components;
    GameObject(std::string name);
    std::string name;
    friend class Scene;
};

// function templates has to defined in header files
template<typename C>
std::shared_ptr<C> GameObject::addComponent() {
    C * c = new C(this);
    auto res = std::shared_ptr<C>(c);
    components.push_back(res);
    return res;
}

template<typename C>
std::shared_ptr<C> GameObject::getComponent() {
    for (auto c : components){
        auto castPtr = std::dynamic_pointer_cast<C>(c);
        if (castPtr != nullptr){
            return castPtr;
        }
    }
    // not found
    return nullptr;
}



