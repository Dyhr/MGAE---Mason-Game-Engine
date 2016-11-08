#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Sprite.h"
#include "SpriteAtlas.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SRE\SimpleRenderEngine.hpp>
#include "Engine.hpp"
#include "Engine2D.h"

using namespace std;

int main(int argc, char** argv) {
    SDL_Window *window;                    // Declare a pointer


    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    int width = 640;
    int height = 480;
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            width,                               // width, in pixels
            height,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );
    SDL_SetWindowTitle(window,"Hello world");
    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

	//spriteRendering(window);

    SRE::SimpleRenderEngine r{window};
	
	Engine e2d;
	e2d.setup();
	e2d.start();
/**
   Engine e;
   e.setup();
   e.start();
   */
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}
