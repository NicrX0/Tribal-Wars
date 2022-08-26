#pragma once
#include "LTexture.h"

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

enum LBuildingButtonSprite
{
	BUILDING_BUTTON_SPRITE_MOUSE_OUT = 0,
	BUILDING_BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUILDING_BUTTON_SPRITE_TOTAL = 2
};

enum Buttons
{
	PLAY_BUTTON = 1,
	QUIT_BUTTON = 2
};

class LButton
{
public:
	LButton();

	LButton(int btnNumber, std::string path);

	LButton(int space, int btnNumber, std::string path);

	void setPosition(int x, int y);

	int handleEvent(int currentState);

	bool isClicked();

	void render();

	void renderBuilding();

	//Accessors

	int getMouseXPos() { return mPosition.x; }
	int getMouseYPos() { return mPosition.y; }

	float getButtonTextureWidth() { return BUTTON_TEXTURE_WIDTH; }
	float getButtonTextureHeight() { return BUTTON_TEXTURE_HEIGHT / BUTTON_SPRITE_TOTAL; }

	float getButtonWidth() { return BUTTON_WIDTH; }
	float getButtonHeight() { return BUTTON_HEIGHT / BUTTON_SPRITE_TOTAL; }

	LButtonSprite getCurrentSprite() { return mCurrentSprite; }

	void getButtonCoords() { std::cout << "X: " << mPosition.x << " Y: " << mPosition.y << "W: " << mButtonHitboxRect.w << " H: " << mButtonHitboxRect.h << std::endl; }

private:

	int buttonNumber;

	float BUTTON_TEXTURE_WIDTH;
	float BUTTON_TEXTURE_HEIGHT;

	float BUTTON_WIDTH;
	float BUTTON_HEIGHT;

	bool _isPressed;
	bool _isReleased;
	bool _buttonClicked;

	SDL_Rect mButtonHitboxRect;

	SDL_Rect mButtonSpriteRect;

	SDL_Rect buttonSpriteClips[BUTTON_SPRITE_TOTAL];

	SDL_Rect currentViewportRect;

	SDL_Point mPosition;

	SDL_Point mPositionTexture;

	LButtonSprite mCurrentSprite;

	//Textures
	LTexture* m_pButtonSpriteTexture;
};

