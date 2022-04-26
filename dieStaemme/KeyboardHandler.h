#pragma once
#include <SDL.h>
#include <iostream>

class KeyboardHandler
{
public:
	KeyboardHandler();
	void checkKeyStates();
	void resetKeyFlags();
	bool getUpState() { return up_flag; }
	bool getDownState() { return down_flag; }
	bool getLeftState() { return left_flag; }
	bool getRightState() { return right_flag; }
	bool getShootState() { return shoot_flag; }



private:

	bool up_flag;
	bool down_flag;
	bool left_flag;
	bool right_flag;
	bool shoot_flag;
};

