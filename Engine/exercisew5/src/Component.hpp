#pragma once
//#include "GameObject.hpp"

class GameObject;

class Component {
public:
    virtual ~Component();
    GameObject* getGameObject();
protected:
    Component(GameObject *gameObject);
    GameObject *gameObject;

    friend class GameObject;
};


