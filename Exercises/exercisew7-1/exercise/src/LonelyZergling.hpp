#pragma once

#include "Component.hpp"

// Example component
class LonelyZergling : public Component{
public:
    void Burrow();
protected:
    LonelyZergling(GameObject *gameObject);
    friend class GameObject;
};
