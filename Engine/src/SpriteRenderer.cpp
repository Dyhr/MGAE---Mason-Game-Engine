#include "Mason/SpriteRenderer.h"

#include "Mason/GameObject.hpp"

using namespace Mason;
using namespace SRE;

SpriteRenderer::SpriteRenderer(std::shared_ptr<GameObject> gameObject):Component(gameObject) {
	transform = gameObject->getComponent<Transform>();
}

void SpriteRenderer::draw() {
	if (sprite) {
		sprite->draw(transform->globalTransform());
	}
}
