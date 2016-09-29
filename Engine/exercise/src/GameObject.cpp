#include "GameObject.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Shader.hpp>
#include "glm/gtx/euler_angles.hpp"

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
    SimpleRenderEngine::instance->draw(mesh,globalTransform(),shader);
}

glm::mat4 GameObject::localTransform() {
    // todo implement (using translate, rotate, scale)
    return glm::eulerAngleX(glm::radians(rotation.x));

}

glm::mat4 GameObject::globalTransform() {
    // todo implement
    return localTransform();
}

