#pragma once


#include <SRE/Mesh.hpp>
#include "glm/glm.hpp"

class GameObject {
public:
    GameObject(SRE::Mesh* mesh, SRE::Shader* shader);

    void draw();

    glm::vec4 color;

    GameObject * parent;
    glm::vec3 position;
    // rotation in degrees (default value 0,0,0)
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 localTransform();
    glm::mat4 globalTransform();
private:
    SRE::Mesh* mesh;
    SRE::Shader* shader;
};


