#include "GameObject.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace SRE;

GameObject::GameObject(Mesh *mesh, Shader *shader)
:mesh(mesh), shader(shader)
{
    color = {1,1,1,1};

    position = {0,0,0};
    rotation = {0,0,0};
    scale = {1,1,1};

    parent = nullptr;
}

void GameObject::draw() {
	shader->setVector("color", color);
    SimpleRenderEngine::instance->draw(mesh,globalTransform(),shader);
}

glm::mat4 GameObject::localTransform() {
    // todo implement (using translate, rotate, scale)
	
	auto translateMat = glm::translate(glm::mat4(1), position);
	auto rotateMat = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
	auto scaleMat = glm::scale(glm::mat4(1), scale);
	auto transform = translateMat * rotateMat * scaleMat;

	return transform;
}

glm::mat4 GameObject::globalTransform() {
    // todo implement
	glm::mat4 transform = localTransform();
	if (parent) {
		auto parentTransform = parent->globalTransform();
		transform = parentTransform * transform;
	}
    return transform;
}

