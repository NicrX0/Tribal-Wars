#include "LButton.h"

LButton::LButton()
{
	mPosition.x = NULL;
	mPosition.y = NULL;

	mPositionTexture.x = NULL;
	mPositionTexture.y = NULL;

	_isPressed = false;
	_isReleased = false;
	_buttonClicked = false;

	//New test code
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::LButton(int btnNumber, std::string path)
{
	buttonNumber = btnNumber;

	_isPressed = false;
	_isReleased = false;
	_buttonClicked = false;

	mPosition.x = NULL;
	mPosition.y = NULL;

	mPositionTexture.x = NULL;
	mPositionTexture.y = NULL;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	//Load button texture
	m_pButtonSpriteTexture = new LTexture;
	if (!m_pButtonSpriteTexture->loadFromFile(path, g_pFramework->GetRenderer()))
	{
		printf("Error loading button texture!\n");
	}

	BUTTON_TEXTURE_WIDTH = m_pButtonSpriteTexture->getWidth();
	BUTTON_TEXTURE_HEIGHT = m_pButtonSpriteTexture->getHeight();

	BUTTON_WIDTH = m_pButtonSpriteTexture->getWidthOld();
	BUTTON_HEIGHT = m_pButtonSpriteTexture->getHeightOld();

	mButtonHitboxRect.w = m_pButtonSpriteTexture->getWidth();
	mButtonHitboxRect.h = m_pButtonSpriteTexture->getHeight() / BUTTON_SPRITE_TOTAL;

	for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
	{
		buttonSpriteClips[i].x = 0; // g_pFramework->getScreenWidthScale();
		buttonSpriteClips[i].y = i * BUTTON_HEIGHT / BUTTON_SPRITE_TOTAL;// / g_pFramework->getScreenHeightScale();
		buttonSpriteClips[i].w = BUTTON_WIDTH;// / g_pFramework->getScreenWidthScale();
		buttonSpriteClips[i].h = BUTTON_HEIGHT / BUTTON_SPRITE_TOTAL; // g_pFramework->getScreenHeightScale();
	}
}

LButton::LButton(int space, int btnNumber, std::string path)
{
	buttonNumber = btnNumber;

	_isPressed = false;
	_isReleased = false;
	_buttonClicked = false;

	mPosition.x = NULL;
	mPosition.y = NULL;

	mPositionTexture.x = NULL;
	mPositionTexture.y = NULL;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	//Load button texture
	m_pButtonSpriteTexture = new LTexture;
	if (!m_pButtonSpriteTexture->loadFromFile(path, g_pFramework->GetRenderer()))
	{
		printf("Error loading button texture!\n");
	}

	mButtonSpriteRect.w = m_pButtonSpriteTexture->getWidth();
	mButtonSpriteRect.h = m_pButtonSpriteTexture->getHeight();

	mButtonHitboxRect.w = m_pButtonSpriteTexture->getWidth() * g_pFramework->getScreenWidthScale();
	mButtonHitboxRect.h = m_pButtonSpriteTexture->getHeight() * g_pFramework->getScreenHeightScale();
}

void LButton::setPosition(int x, int y)
{
	currentViewportRect = g_pFramework->getCurrentViewportRect();

	mPosition.x = x + currentViewportRect.x;
	mPosition.y = y + currentViewportRect.y;

	mPositionTexture.x = x;
	mPositionTexture.y = y;
}


int LButton::handleEvent(int currentState)
{
	//If mouse event happened
	if (g_pFramework->globalEvent.type == SDL_MOUSEMOTION || g_pFramework->globalEvent.type == SDL_MOUSEBUTTONDOWN || g_pFramework->globalEvent.type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//std::cout << "Mouse moved. X: " << x << " Y: " << y << std::endl;

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x){ inside = false; }
		//Mouse is right of the button
		else if (x > mPosition.x + mButtonHitboxRect.w) { inside = false; }
		//Mouse is above the button
		else if (y < mPosition.y) { inside = false; }
		//Mouse is below the button
		else if (y > mPosition.y + mButtonHitboxRect.h) { inside = false; }

		//Mouse is outside button
		if (!inside)
		{ 
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
			_isPressed = false; //Reset button state if mouse leaves button while _isPressed
		}

		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (g_pFramework->globalEvent.type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				//printf("Mouse moved.\n");
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				_isPressed = true;
				//printf("Button clicked.\n");
				break;

			case SDL_MOUSEBUTTONUP:	
				if(isClicked())
				{
					if (_buttonClicked)
					{
						_buttonClicked = false;
					}
					else if (!_buttonClicked)
					{
						_buttonClicked = true;
					}
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT; //reset sprite after click
					return buttonNumber;
				}
				break;
			break;
			}
		}
	}
	return currentState; //return old value if nothing changed
}

bool LButton::isClicked()
{
	if (_isPressed)
	{
		_isPressed = false;
		_isReleased = true;
		//printf("Button was clicked.\n");
		return true;
	}
	else
	{
		return false;
	}
}

void LButton::render()
{
	//Show current button sprite
	m_pButtonSpriteTexture->render(mPositionTexture.x, mPositionTexture.y, &buttonSpriteClips[mCurrentSprite]);
}

void LButton::renderBuilding()
{
	//Show current button sprite
	//std::cout << "X: " << mPosition.x << " Y: " << mPosition.y << " W: " << mButtonSpriteRect.w << " H: " << mButtonSpriteRect.h << std::endl;
	m_pButtonSpriteTexture->render(mPositionTexture.x, mPositionTexture.y, &mButtonSpriteRect);
}