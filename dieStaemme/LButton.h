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

class LButton
{
public:
	LButton();

	LButton(int btnNumber, std::string path);

	LButton(int x, int y, int w, int h);

	void setPosition(int x, int y);

	int handleEvent(int choice);

	int handleBuildingEvent(enum BuildingType);

	bool isClicked();

	void render();

	//Accessors

	int getMouseXPos() { return mPosition.x; }
	int getMouseYPos() { return mPosition.y; }

	float getButtonTextureWidth() { return BUTTON_TEXTURE_WIDTH; }
	float getButtonTextureHeight() { return BUTTON_TEXTURE_HEIGHT / BUTTON_SPRITE_TOTAL; }

	float getButtonWidth() { return BUTTON_WIDTH; }
	float getButtonHeight() { return BUTTON_HEIGHT / BUTTON_SPRITE_TOTAL; }

	LButtonSprite getCurrentSprite() { return mCurrentSprite; }

	void getButtonCoords() { std::cout << "X: " << mButtonHitboxRect.x << " Y: " << mButtonHitboxRect.y << "W: " << mButtonHitboxRect.w << " H: " << mButtonHitboxRect.h << std::endl; }

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

	SDL_Point mPosition;

	LButtonSprite mCurrentSprite;

	//Textures
	LTexture* m_pButtonSpriteTexture;
};

