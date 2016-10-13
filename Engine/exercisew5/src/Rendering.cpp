#include "Rendering.h"
#include "SRE/SimpleRenderEngine.hpp"

Rendering::Rendering(GameObject *gameObject)
:Component(gameObject) {
	transform = gameObject->getComponent<Transform>();
	color = glm::vec4{ 1, 1, 1, 1 };
}

void Rendering::draw() {
	if (transform) {
		shader->setVector("color", color);
		SRE::SimpleRenderEngine::instance->draw(mesh.get, transform.get.globalTransform(), shader.get);
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