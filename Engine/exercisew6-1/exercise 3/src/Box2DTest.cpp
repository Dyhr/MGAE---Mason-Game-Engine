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


using namespace glm;
using namespace SRE;

b2World* Box2DTest::world;

Box2DTest::Box2DTest(int width, int height) {
    this->width = width;
    this->height = height;
    
    //TODO: Initialize your world from here!
    Box2DTest::world = new b2World(b2Vec2(0,-9.89f));
 
    
    //TODO: Implement make  Box2DTest extend b2ContactListener, to allow for collision handling!
    //world->SetContactListener(this);
    
    
    //TODO: Set your debug Draw instance here!
    //world->SetDebugDraw(b2Draw *debugDraw);
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
        
        //Debug Draw your physics
        world->DrawDebugData();

        sre->swapWindow();
        SDL_Delay(16);
    }
}

//TODO: implement BeginContact from the contactListener, to handle collisions
//void BeginContact(b2Contact* contact)

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
                    //TODO: Implement your keyboard handling logic here!
                    std::cout << "Test" << std::endl;
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

