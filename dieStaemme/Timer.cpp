#include "Timer.h"

Timer::Timer()
{
	//Initialization
	m_fCurTime = 0.0f;
	m_fLastTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = 0.0f;
}

void Timer::Update()
{
	m_fCurTime = SDL_GetTicks() / 1000.0f;
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime;
	//std::cout << "Time for last frame: " << m_fElapsed << " seconds." << std::endl;
	//std::cout << "Time overall: " << m_fCurTime << " seconds." << std::endl;
}