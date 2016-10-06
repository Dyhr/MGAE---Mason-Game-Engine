#include <SRE/Shader.hpp>
#include "Box2DTest.hpp"
#include "SDL.h"
#include "glm/gtc/matrix_transform.hpp"
#include "SRE/Debug.hpp"
#include "SRE/Text.hpp"
#include "SRE/Texture.hpp"
#include <iostream>
#include <glm/gtx/closest_point.hpp>
#include <time.h>       /* time */

#include "SREDebugDraw.h"


using namespace glm;
using namespace SRE;

b2World* Box2DTest::world;

void Box2DTest::initWorld(b2World* world) {
	b2PolygonShape pillar1bottom;
	b2PolygonShape pillar1top;
	b2PolygonShape pillar2bottom;
	b2PolygonShape pillar2top;
	b2PolygonShape pillar3;
	b2PolygonShape pillar4top;
	b2PolygonShape pillar4bottom;

	b2EdgeShape floor;
	floor.Set(b2Vec2(0, 20), b2Vec2(640, 20));

	b2EdgeShape ceiling;
	ceiling.Set(b2Vec2(0, 460), b2Vec2(640, 460));


	pillar1bottom.SetAsBox(20, 80, b2Vec2(240, 100), 0.0f);
	pillar1top.SetAsBox(20, 100, b2Vec2(240, 360), 0.0f);
	pillar2bottom.SetAsBox(20, 120, b2Vec2(360, 140), 0.0f);
	pillar2top.SetAsBox(20, 60, b2Vec2(360, 400), 0.0f);
	pillar3.SetAsBox(20, 180, b2Vec2(480, 200), 0.0f);
	pillar4bottom.SetAsBox(20, 100, b2Vec2(600, 120), 0.0f);
	pillar4top.SetAsBox(20, 80, b2Vec2(600, 380), 0.0f);


	b2BodyDef birdbd;
	birdbd.position.Set(30, 40);
	birdbd.type = b2_dynamicBody;
	birdbd.fixedRotation = true;
	birdbody = world->CreateBody(&birdbd);

	b2CircleShape bird;
	bird.m_radius = 10;
	b2FixtureDef fd;
	fd.shape = &bird;
	fd.density = 20.0f;
	fd.friction = 1.0f;

	birdbody->CreateFixture(&fd);


	b2BodyDef bd;
	b2Body* ground = world->CreateBody(&bd);//ground includes all the elements in the game world

	ground->CreateFixture(&pillar1bottom, 0.0f);
	ground->CreateFixture(&pillar1top, 0.0f);
	ground->CreateFixture(&pillar2bottom, 0.0f);
	ground->CreateFixture(&pillar2top, 0.0f);
	ground->CreateFixture(&pillar3, 0.0f);
	ground->CreateFixture(&pillar4top, 0.0f);
	ground->CreateFixture(&pillar4bottom, 0.0f);
	ground->CreateFixture(&floor, 0.0f);
	ground->CreateFixture(&ceiling, 0.0f);
}

void Box2DTest::update() {
	if (reset) {
		reset = false;
		birdbody->SetTransform(b2Vec2(30, 40), 0);
		hasLeftTheGround = 0;
		birdbody->SetLinearVelocity(b2Vec2(0, 0));
	}

	if (hasLeftTheGround) {
		b2Vec2 v = birdbody->GetLinearVelocity();
		v.x = 50;
		birdbody->SetLinearVelocity(v);
	}
}

Box2DTest::Box2DTest(int width, int height) {
    this->width = width;
    this->height = height;
    
    Box2DTest::world = new b2World(b2Vec2(0,-500));
	initWorld(world);
 
    world->SetContactListener(this);
    
	auto debugDraw = new SREDebugDraw();
    world->SetDebugDraw(debugDraw);
	debugDraw->SetFlags(b2Draw::e_shapeBit);
}

Box2DTest::~Box2DTest() {
    delete Box2DTest::world;
    Box2DTest::world = nullptr;
}

void Box2DTest::startGameLoop() {
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

    sre->getCamera()->setWindowCoordinates();
    
    while (quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

        sre->clearScreen(vec4(0.3f,0.3f,0.3f,1));

        HandleSDLEvents();
        
        //Update physics
        world->Step(1/60.f, 10, 10);

		update();
        
        //Debug Draw your physics
        world->DrawDebugData();

        sre->swapWindow();
        SDL_Delay(16);
    }
}

void Box2DTest::BeginContact(b2Contact* contact) {
	if (hasLeftTheGround) {
		reset = true;
	}
}

void Box2DTest::HandleSDLEvents()
{
    // message processing loop
    SDL_Event event;
    /* Poll for events */
    while( SDL_PollEvent( &event ) ){
        
        switch( event.type ){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE)
                {
					float impulse = birdbody->GetMass() * 5000000000;
					birdbody->ApplyForceToCenter(b2Vec2(0, impulse), true);
					hasLeftTheGround = true;
                }
                break;
                /* SDL_QUIT event (window close) */
            case SDL_QUIT:
                quit = 1;
                break;
                
            default:
                break;
        }
        
    }
}

