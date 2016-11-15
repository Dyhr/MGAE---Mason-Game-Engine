#pragma once
#include <SDL.h>
#include <iostream>
#include "Engine.hpp"
#include <cstring>

class InputManage {
public:
	
	InputManage();
	static InputManage* getInstance();
	void KeyDown(SDL_Event event);
	bool toggleGUI;
private:
	static InputManage* instance;
	
};