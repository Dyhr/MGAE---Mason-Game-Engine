#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "GameObject.hpp"

class Engine {
public:
    void setup();
    void start();
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};


