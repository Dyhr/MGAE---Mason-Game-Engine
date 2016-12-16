#include "Mason/GameObject.hpp"

#include "Mason/Script.hpp"

using namespace Mason;

std::map<std::string, Script*(*)(std::shared_ptr<GameObject>)> Script::scripts = std::map<std::string, Script*(*)(std::shared_ptr<GameObject>)>();

GameObject::GameObject(std::string name_) :name(name_)
{
}

GameObject::~GameObject() {

}

std::shared_ptr<Script> GameObject::addScript(std::string name)
{
	Script* c = Script::scripts[name](std::shared_ptr<GameObject>(this));
	auto res = std::shared_ptr<Script>(c);
	components.push_back(res);
	return res;
}

void GameObject::setName(std::string nm)
{
	name = nm;
}

std::string GameObject::getName() const
{
	return name;
}

std::shared_ptr<Transform> GameObject::getTransform() const
{
	return this->transform;
}
void GameObject::setTransform(std::shared_ptr<Transform> tr) {
	this->transform = tr;
}

bool GameObject::removeComponent(std::shared_ptr<Component> ptr) {
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		if (*iter == ptr) {
			components.erase(iter);
			ptr.reset();
			return true;
		}
	}
	return false;
}
