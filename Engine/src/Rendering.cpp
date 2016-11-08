#include "Rendering.h"

#include "SRE\Texture.hpp"
#include <SRE\SimpleRenderEngine.hpp>

Rendering::Rendering(GameObject *gameObject)
:Component(gameObject) {
	transform = gameObject->getComponent<Transform>();
	color = glm::vec4{ 1, 1, 1, 1 };
}

void Rendering::draw() {
	if (transform) {
		shader->setVector("color", color);
		shader->set("tex", SRE::Texture::getWhiteTexture());
		SRE::SimpleRenderEngine::instance->draw(&*mesh, transform->globalTransform(), &*shader);
	}
}

void Rendering::loadMesh(std::shared_ptr<SRE::Mesh> mesh) {
	this->mesh = mesh;
}

void Rendering::loadShader(std::shared_ptr<SRE::Shader> shader) {
	this->shader = shader;
}

void Rendering::setColor(glm::vec4 color) {
	this->color = color;
}	