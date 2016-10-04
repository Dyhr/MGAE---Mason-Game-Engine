#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"

class Box2DTest {
public:
    Box2DTest(int width, int height);
    virtual ~Box2DTest();
    void startGameLoop();
    static b2World* world;
    void HandleSDLEvents();
    
private:

    int width;
    int height;
    int quit;
};

