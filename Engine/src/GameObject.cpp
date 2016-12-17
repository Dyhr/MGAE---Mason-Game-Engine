#include "Mason/GameObject.hpp"

#include "Mason/Script.hpp"

using namespace Mason;

std::map<std::string, Script*(*)(std::shared_ptr<GameObject>)> Script::scripts = std::map<std::string, Script*(*)(std::shared_ptr<GameObject>)>();

GameObject::GameObject(std::string name_) :name(name_)
{
}

GameObject::~GameObject() {
	
}

Script* GameObject::addScript(std::string name)
{
	Script* c = Script::scripts[name](std::shared_ptr<GameObject>(this));
	components.push_back(c);
	return c;
}

void GameObject::setName(std::string nm)
{
	name = nm;
}

std::string GameObject::getName() const
{
	return name;
}

Transform* GameObject::getTransform() const
{
	return this->transform;
}
void GameObject::setTransform(Transform* tr) {
	this->transform = tr;
}

bool GameObject::removeComponent(Component* ptr) {
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		if (*iter == ptr) {
			components.erase(iter);
			delete ptr;
			return true;
		}
	}
	return false;
}
