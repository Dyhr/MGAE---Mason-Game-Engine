#pragma once
#include <SDL.h>
#include <iostream>
#include "Engine.hpp"
#include <cstring>

class InputManage {
public:
	
	InputManage();
	bool getToggle();
	void KeyDown(SDL_Event event);
private:
	bool toggleGUI;
};