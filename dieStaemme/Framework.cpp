#include "Framework.h"

bool Framework::Init(int ScreenWidth, int ScreenHeight)
{
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = ScreenHeight;

	bool success = true;

	gWindow = SDL_CreateWindow("Tribal Wars", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Couldn't create SDL window. Error: %s\n", SDL_GetError();
		success = false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	if (gRenderer == NULL)
	{
		std::cout << "Couldn't create SDL renderer. Error: %s\n", SDL_GetError();
		success = false;
	}
	else
	{
		//Calc aspect ratio scale and set to renderer (basewidth: 800px | baseheight: 600px)
		float x_temp = 100.0f / 800.0f * getScreenWidth() / 100.0f;
		float y_temp = 100.0f / 600.0f * getScreenHeight() / 100.0f;

		m_ScreenWidthScale = x_temp;
		m_ScreenHeightScale = y_temp;

		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}

		//Initialize SDL_ttf and load font
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}

		gFont = TTF_OpenFont("assets/SemiCasual.ttf", 25);
		if (gFont == NULL)
		{
			printf("Failed to load SemiCasual font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
	}

	m_pKeyboard = new KeyboardHandler;
	e = new SDL_Event;
	return success;
}

void Framework::Quit()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	//Free global font
	TTF_CloseFont(gFont);

	gRenderer = NULL;
	gWindow = NULL;
	gFont = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Framework::Update()
{
	g_pTimer->Update();

	//Check keyboardstate and set flags for pressed keys
	m_pKeyboard->checkKeyStates();
	up_pressed = m_pKeyboard->getUpState();
	down_pressed = m_pKeyboard->getDownState();
	left_pressed = m_pKeyboard->getLeftState();
	right_pressed = m_pKeyboard->getRightState();
	shoot_pressed = m_pKeyboard->getShootState();

	SDL_PumpEvents();
}


void Framework::Clear()
{
	//Fill buffer(Surface) with backgroundcolor (black)
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 0, 0, 0));
}

void Framework::Render()
{
	SDL_RenderPresent(gRenderer);
}

void Framework::resetKeyFlags()
{
	m_pKeyboard->resetKeyFlags();
}