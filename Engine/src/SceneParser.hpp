#pragma once

#include <string>
#include <vector>
#include "glm/glm.hpp"
#include <SRE\Mesh.hpp>
#include "GameObject.hpp"


class GameObjectDescriptor{
public:
    // Uniquely defines a game object
    int uniqueId;

    // valid values are: "plane", "cube" and "sphere"
    std::string meshName;
    
    // object color
    glm::vec4 color;
    
    // transform
    // position relative to parent
    glm::vec3 position;
    // rotation relative to parent
    glm::vec3 rotationEuler;
    // scale relative to parent
    glm::vec3 scale;
    
    // parent id (-1 means no parent)
    int parentId;
};



class SceneParser{
public:
    static std::vector<GameObjectDescriptor> parseFile(std::string filename);
};
