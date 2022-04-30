#include "Building.h"

Building::Building()
{
	mPosition.x = NULL;
	mPosition.y = NULL;

	//New test code
	mCurrentSprite = MAIN_BUILDING;

	int level = 0;
}

Building::Building(int type)
{
	//buttonNumber = btnNumber;

	_isPressed = false;
	_isReleased = false;
	_buttonClicked = false;

	mPosition.x = NULL;
	mPosition.y = NULL;

	m_pBuildingTexture = new LTexture;
	switch (type)
	{
	case MAIN_BUILDING:
		//Load texture
		if (!m_pBuildingTexture->loadFromFile("assets/village/main_building_0.png", g_pFramework->GetRenderer()))
		{
			printf("Error loading main_building_0.png\n");
		}

		//Set position
		m_pBuildingTexture->SetPos(g_pFramework->getScreenWidth() / 2 - m_pBuildingTexture->getWidth() / 2, g_pFramework->getScreenHeight() / 2 - m_pBuildingTexture->getHeight() / 2);
		break;

	default:
		printf("Error creating building -> unknown type.\n");
		break;
	}

	BUILDING_TEXTURE_WIDTH = m_pBuildingTexture->getWidth();
	BUILDING_TEXTURE_HEIGHT = m_pBuildingTexture->getHeight();

	BUILDING_WIDTH = m_pBuildingTexture->getWidthNew();
	BUILDING_HEIGHT = m_pBuildingTexture->getHeightNew();

	mBuildingHitboxRect.w = m_pBuildingTexture->getWidth();
	mBuildingHitboxRect.h = m_pBuildingTexture->getHeight() / BUTTON_SPRITE_TOTAL;

	m_pBuildingButton = new LButton(g_pFramework->getScreenWidth() / 2 - BUILDING_TEXTURE_WIDTH / 2, g_pFramework->getScreenHeight() * 0.66f, mBuildingHitboxRect.w, mBuildingHitboxRect.h);
	m_pBuildingButton->setPosition(0, 0);
}

Building::~Building()
{
	m_pBuildingTexture->free();
}

void Building::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

int Building::handleEvent(enum BuildingType building)
{

	m_pBuildingButton->handleBuildingEvent(building);

	return 1; //return old value if nothing changed
}

bool Building::isClicked()
{
	if (_isPressed)
	{
		_isReleased = true;
		printf("Button was clicked.\n");
		return true;
	}
	else
	{
		return false;
	}
}

void Building::render()
{
	//Show current button sprite
	m_pBuildingTexture->render(mPosition.x, mPosition.y);
}