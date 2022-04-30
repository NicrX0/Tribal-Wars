#pragma once
#include "Timer.h"
#include <SDL_image.h>
#include<SDL_ttf.h>
#include "KeyboardHandler.h"

#define g_pFramework Framework::Get()

class Framework : public TSingleton<Framework>
{
public:

	bool Init(int ScreenWidth, int ScreenHeight);
	void Quit();
	void Update();
	void Clear();
	void Render();
	void resetKeyFlags();

	SDL_Surface* GetScreen() { return m_pScreen; }
	SDL_Renderer* GetRenderer() { return gRenderer; }
	TTF_Font* GetFont() { return gFont; }
	float getScreenWidth() { return m_ScreenWidth; }
	float getScreenHeight() { return m_ScreenHeight; }

	//Aspect ratio accessors
	float getScreenWidthScale() { return m_ScreenWidthScale; }
	float getScreenHeightScale() { return m_ScreenHeightScale; }

	//Keyboard accessors
	bool getUpKeystate() { return up_pressed; }
	bool getDownKeystate() { return down_pressed; }
	bool getLeftKeystate() { return left_pressed; }
	bool getRightKeystate() { return right_pressed; }
	bool getShootKeystate() { return shoot_pressed; }

	SDL_Event globalEvent;

private:

	float m_ScreenWidth;
	float m_ScreenHeight;

	float m_ScreenWidthScale;
	float m_ScreenHeightScale;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Surface* gSurface;

	//Globally used font
	TTF_Font* gFont;

	SDL_Surface* m_pScreen;

	//Keyboard handling
	KeyboardHandler* m_pKeyboard;
	bool up_pressed, down_pressed, left_pressed, right_pressed, shoot_pressed;
};



