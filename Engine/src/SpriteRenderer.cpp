#include "SpriteRenderer.h"
#include "GameObject.hpp"

using namespace SRE;

SpriteRenderer::SpriteRenderer(GameObject *gameObject):Component(gameObject) {
	transform = gameObject->getComponent<Transform>();
}

void SpriteRenderer::draw() {
	if (sprite) {
		auto position = glm::vec3(transform->globalTransform()[3]);
		sprite->draw(position);
	}
}
