#include "Mason/Component.hpp"

using namespace Mason;

Component::Component(GameObject *gameObject)
	:gameObject(gameObject)
{
}

Component::~Component() {
}

GameObject *Component::getGameObject() {
	return gameObject;
}