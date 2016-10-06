#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"

class Box2DTest : public b2ContactListener {
public:
    Box2DTest(int width, int height);
    virtual ~Box2DTest();
    void startGameLoop();
    static b2World* world;
    void HandleSDLEvents();

	void BeginContact(b2Contact* contact);

private:

	void initWorld(b2World* world);
	void update();

    int width;
    int height;
    int quit;

	b2Body* birdbody;
	bool hasLeftTheGround = false;
	bool reset = false;
};

