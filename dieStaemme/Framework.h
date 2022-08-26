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
	void setFullscreenViewport() { SDL_RenderSetViewport(gRenderer, &fullscreenViewport), currentViewportRect = fullscreenViewport; }
	void setTopViewport() { SDL_RenderSetViewport(gRenderer, &topViewport), currentViewportRect = topViewport; }
	void setBottomViewport() { SDL_RenderSetViewport(gRenderer, &bottomViewport), currentViewportRect = bottomViewport; }
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

	//Viewport accessors
	SDL_Rect getCurrentViewportRect() { return currentViewportRect; }

	float getBottomViewportX_Base() { std::cout << "X_Base: " << bottomViewport.x << std::endl; return bottomViewport.x; }
	float getBottomViewportY_Base() { std::cout << "Y_Base: " << bottomViewport.y << std::endl; return bottomViewport.y; }
	float getBottomViewportWidth() { return bottomViewport.w; }
	float getBottomViewportHeight() { return bottomViewport.h; }

	float getTopViewportX_Base() { return topViewport.x; }
	float getTopViewportY_Base() { return topViewport.y; }
	float getTopViewportWidth() { return topViewport.w; }
	float getTopViewportHeight() { return topViewport.h; }

	float getFullscreenViewportX_Base() { return fullscreenViewport.x; }
	float getFullscreenViewportY_Base() { return fullscreenViewport.y; }
	float getFullscreenViewportWidth() { return fullscreenViewport.w; }
	float getFullscreenViewportHeight() { return fullscreenViewport.h; }

	int getTPS() { return TicksPerSecond; }

	SDL_Event globalEvent;

private:

	float m_ScreenWidth;
	float m_ScreenHeight;

	float m_ScreenWidthScale;
	float m_ScreenHeightScale;

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Surface* gSurface;

	int Tickcounter;
	int TicksPerSecond;

	//Globally used font
	TTF_Font* gFont;

	SDL_Surface* m_pScreen;

	//Keyboard handling
	KeyboardHandler* m_pKeyboard;
	bool up_pressed, down_pressed, left_pressed, right_pressed, shoot_pressed;

	//Viewports
	SDL_Rect currentViewportRect;
	SDL_Rect fullscreenViewport;
	SDL_Rect topViewport;
	SDL_Rect bottomViewport;
};



