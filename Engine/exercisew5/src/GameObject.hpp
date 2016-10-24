#pragma once

#include <string>
#include <vector>
#include "Component.hpp"
#include <memory>

// forward declaration
class Scene;

class GameObject {
public:
    ~GameObject();
	GameObject(std::string name);

    std::string getName();
    template<typename C>
    std::shared_ptr<C> addComponent();

    bool removeComponent(std::shared_ptr<Component> ptr);

    template<typename C>
    std::shared_ptr<C> getComponent();
	template<typename C>
	std::vector<std::shared_ptr<C>> getComponents();

private:
    std::vector<std::shared_ptr<Component>> components;
    
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
        if (castPtr != nullptr)
            return castPtr;
    }
    // not found
    return nullptr;
}
template<typename C>
std::vector<std::shared_ptr<C>> GameObject::getComponents() {
	std::vector<std::shared_ptr<C>> result;
	for(auto c : components) {
		auto castPtr = std::dynamic_pointer_cast<C>(c);
		if(castPtr != nullptr)
			result.push_back(castPtr);
	}
	return result;
}
