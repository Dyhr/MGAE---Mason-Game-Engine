
#include "InputManage.h"
InputManage::InputManage() {
	this->toggleGUI = false;
}
InputManage* InputManage::instance = nullptr;

InputManage* InputManage::getInstance()
{
	if (instance == nullptr) instance = new InputManage();
	return instance;
}
//should we pass it by reference?
void InputManage::KeyDown(SDL_Event event) {
	char input;
	

	//only for letters for the moment
	if (event.key.keysym.sym < 0x80 && event.key.keysym.sym > 0) {
		input = (char)event.key.keysym.sym; //virtual keycode
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
	}
}