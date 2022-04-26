#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler()
{
	up_flag = false;
	down_flag = false;
	left_flag = false;
	right_flag = false;
	shoot_flag = false;
}

void KeyboardHandler::resetKeyFlags()
{
	up_flag = false;
	down_flag = false;
	left_flag = false;
	right_flag = false;
	shoot_flag = false;
}


void KeyboardHandler::checkKeyStates()
{
	up_flag = false;
	down_flag = false;
	left_flag = false;
	right_flag = false;

	//Check for keyboard inputs
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	//std::cout << "scanning for keystate.\n" << std::endl;

	if (keystates[SDL_SCANCODE_UP])
	{
		up_flag = true;
		//std::cout << "UP pressed." << std::endl;
	}
	if (keystates[SDL_SCANCODE_DOWN])
	{
		down_flag = true;
		//std::cout << "DOWN pressed." << std::endl;
	}
	if (keystates[SDL_SCANCODE_LEFT])
	{
		left_flag = true;
		//std::cout << "LEFT pressed." << std::endl;
	}
	if (keystates[SDL_SCANCODE_RIGHT])
	{
		right_flag = true;
		//std::cout << "RIGHT pressed." << std::endl;
	}
	if (keystates[SDL_SCANCODE_A])
	{
		shoot_flag = true;
		//std::cout << "Shoot key (A) pressed.\n";
	}
	if (!keystates[SDL_SCANCODE_A])
	{
		shoot_flag = false;
		//std::cout << "Shoot key (A) released.\n";
	}
}
