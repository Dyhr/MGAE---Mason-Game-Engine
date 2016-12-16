#include "Mason/Component.hpp"
#include <memory>

using namespace Mason;

Component::Component(std::shared_ptr<GameObject> gameObject)
	:gameObject(gameObject)
{
}

Component::~Component() {
}

std::shared_ptr<GameObject> Component::getGameObject() {
	return gameObject;
}