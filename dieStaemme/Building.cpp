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

int Building::handleEvent()//SDL_Event* e, int choice)
{
	//m_pBuildingButton->getButtonCoords();
	m_pBuildingButton->handleEvent(&g_pFramework->e, 1);
	/*while (SDL_PollEvent(&g_pFramework->e))
	{
		//If mouse event happened
		if (g_pFramework->e.type == SDL_MOUSEMOTION || g_pFramework->e.type == SDL_MOUSEBUTTONDOWN || g_pFramework->e.type == SDL_MOUSEBUTTONUP)
		{
			//Get mouse position
			int x, y;
			SDL_GetMouseState(&x, &y);

			//std::cout << "Mouse moved. X: " << x << " Y: " << y << std::endl;

			//Check if mouse is in button
			bool inside = true;

			//Mouse is left of the button
			if (x < mPosition.x) { inside = false; }
			//Mouse is right of the button
			else if (x > mPosition.x + mBuildingHitboxRect.w) { inside = false; }
			//Mouse is above the button
			else if (y < mPosition.y) { inside = false; }
			//Mouse is below the button
			else if (y > mPosition.y + mBuildingHitboxRect.h) { inside = false; }

			//Mouse is outside button
			if (!inside)
			{
				mCurrentSprite = MAIN_BUILDING;
				_isPressed = false; //Reset button state if mouse leaves button while _isPressed
			}

			//Mouse is inside button
			else
			{
				//Set mouse over sprite
				switch (g_pFramework->e.type)
				{
				case SDL_MOUSEMOTION:
					mCurrentSprite = MAIN_BUILDING;
					printf("Mouse moved.\n");
					break;

				case SDL_MOUSEBUTTONDOWN:
					mCurrentSprite = MAIN_BUILDING;
					_isPressed = true;
					printf("Button clicked.\n");
					break;

				case SDL_MOUSEBUTTONUP:
					mCurrentSprite = MAIN_BUILDING;
					if (isClicked());
					{
						return buttonNumber;
					}
					break;
					break;
				}
			}
		}
	}
	*/
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