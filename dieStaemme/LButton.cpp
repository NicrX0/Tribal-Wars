#include "LButton.h"

LButton::LButton()
{
	mPosition.x = NULL;
	mPosition.y = NULL;

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

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	//Load button texture
	m_pButtonSpriteTexture = new LTexture;
	if (!m_pButtonSpriteTexture->loadFromFile(path, g_pFramework->GetRenderer()))
	{
		printf("Error loading button texture!\n");
	}

	BUTTON_TEXTURE_WIDTH = m_pButtonSpriteTexture->getWidth();
	BUTTON_TEXTURE_HEIGHT = m_pButtonSpriteTexture->getHeight();

	BUTTON_WIDTH = m_pButtonSpriteTexture->getWidthNew();
	BUTTON_HEIGHT = m_pButtonSpriteTexture->getHeightNew();

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

LButton::LButton(int x, int y, int w, int h)
{
	_isPressed = false;
	_isReleased = false;
	_buttonClicked = false;

	mPosition.x = x;
	mPosition.y = y;

	mButtonHitboxRect.w = w;
	mButtonHitboxRect.h = h;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent()
{
	//If mouse event happened
	if (g_pFramework->e->type == SDL_MOUSEMOTION || g_pFramework->e->type == SDL_MOUSEBUTTONDOWN || g_pFramework->e->type == SDL_MOUSEBUTTONUP)
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
		else if (x > mPosition.x + mButtonHitboxRect.w) { inside = false; }
		//Mouse is above the button
		else if (y < mPosition.y) { inside = false; }
		//Mouse is below the button
		else if (y > mPosition.y + mButtonHitboxRect.h) { inside = false; }

		//Mouse is outside button
		if (!inside)
		{
			_isPressed = false; //Reset button state if mouse leaves button while _isPressed
		}

		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (g_pFramework->e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				printf("Mouse moved.\n");
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				_isPressed = true;
				printf("Button clicked.\n");
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				if (isClicked());
				{
					
				}
				break;
				break;
			}
		}
	}
}

int LButton::handleEvent(SDL_Event* e, int choice)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
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
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				printf("Mouse moved.\n");
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				_isPressed = true;
				printf("Button clicked.\n");
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				if(isClicked());
				{
					return buttonNumber;
				}
				break;
			break;
			}
		}
	}
	return choice; //return old value if nothing changed
}

bool LButton::isClicked()
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

void LButton::render()
{
	//Show current button sprite
	m_pButtonSpriteTexture->render(mPosition.x, mPosition.y, &buttonSpriteClips[mCurrentSprite]);
}