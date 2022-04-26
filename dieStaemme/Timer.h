#pragma once
#include <SDL.h>
#include <iostream>
#include "Singleton.h"

#define g_pTimer Timer::Get()

class Timer : public TSingleton<Timer>
{
public:
	Timer();
	void Update();
	float getElapsed() { return m_fElapsed; }
	float getCurTime() { return m_fCurTime; }

private:
	float m_fElapsed; //Time since last frame
	float m_fCurTime; //Current time
	float m_fLastTime; //Time for last frame
};
