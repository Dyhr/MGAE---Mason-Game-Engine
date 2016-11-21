#include "Mason/InputManager.h"

#include <iostream>


using namespace Mason;

InputManager::InputManager() {
	this->toggleGUI = false;
}
InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance()
{
	if (instance == nullptr) instance = new InputManager();
	return instance;
}

void InputManager::KeyDown(SDL_Event event) {
	char input;
	

	//only for letters for the moment
	if (event.key.keysym.sym < 0x80 && event.key.keysym.sym > 0) {
		input = char(event.key.keysym.sym); //virtual keycode
		std::cout << input << " ";
	}
	else {
		input = '0';
	}

	switch (input)
	{
	case 'm': //show debug menu
		
		this->toggleGUI = !this->toggleGUI;
		break;

	case '0': //default
		break;
	default: break;
	}
}