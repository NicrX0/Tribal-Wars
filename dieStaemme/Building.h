#pragma once
#include "LButton.h"

enum BuildingType
{
	MAIN_BUILDING = 0,
	BUILDING_TYPES_TOTAL = 1
};

class Building
{
public:
	Building();
	Building(int type, int x_pos, int y_pos);
	~Building();

	void setPosition(int x, int y);

	int handleEvent(enum BuildingType);

	bool isClicked();

	void render();

	//Accessors

	int getMouseXPos() { return mPosition.x; }
	int getMouseYPos() { return mPosition.y; }

	float getBuildingTextureWidth() { return BUILDING_TEXTURE_WIDTH; }
	float getBuildingTextureHeight() { return BUILDING_TEXTURE_HEIGHT / BUTTON_SPRITE_TOTAL; }

	float getBuildingWidth() { return BUILDING_WIDTH; }
	float getBuildingHeight() { return BUILDING_HEIGHT / BUTTON_SPRITE_TOTAL; }

private:
	int buttonNumber;

	int level;

	bool _isPressed;
	bool _isReleased;
	bool _buttonClicked;

	float BUILDING_TEXTURE_WIDTH;
	float BUILDING_TEXTURE_HEIGHT;

	float BUILDING_WIDTH;
	float BUILDING_HEIGHT;

	//SDL_Rect buildingSpriteClips[BUTTON_SPRITE_TOTAL];

	SDL_Rect mBuildingHitboxRect;

	SDL_Point mPosition;

	BuildingType mCurrentSprite;

	LTexture* m_pBuildingTexture;

	LButton* m_pBuildingButton;
};

