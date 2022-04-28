#include "Game.h"

Game::Game()
{

}

bool Game::Initialize(SDL_Renderer* renderer)
{
	bool success = true;

	//Create assets and load graphics
	if (!loadMedia(renderer))
	{
		printf("Failed to load media!\n");
	}

	selectedScreen = 1;
	m_iMainMenu = 0;
	m_bGameRun = true;
	return success;
}

void Game::Run()
{
	//Keyboard handler
	KeyboardHandler keyboard;

	//Event handler
	SDL_Event e;

	//Init test village
	m_pVillage = new Village;

	//Mainloop

	while (m_bGameRun == true)
	{
		switch (selectedScreen)
		{
		case 1:
			selectedScreen = showMainmenu(selectedScreen);
			break;
		case 2:
			selectedScreen = showGameScreen(selectedScreen);
			break;
		default:
			//errorscreen();
			break;
		}
		//Update framework and clear buffer
		g_pFramework->Update();

		//Update screen
		g_pFramework->Render();

		//test
		processEvents();

		//Reset Keyboard state
		g_pFramework->resetKeyFlags();
	}
}

void Game::Quit()
{
	
}

bool Game::loadMedia(SDL_Renderer* renderer)
{
	bool success = true;

	//Load main screen start
	//Textures
	m_pGreyBackgroundTexture = new LTexture;
	if (!m_pGreyBackgroundTexture->loadFromFile("assets/grey_background.png", g_pFramework->GetRenderer()))
	{
		printf("Error loading grey_background.png\n");
		success = false;
	}

	//Buttons

	m_pPlayButton = new LButton(1, "assets/play_button.png");
	m_pPlayButton->setPosition(g_pFramework->getScreenWidth() * 0.5f - m_pPlayButton->getButtonTextureWidth() * 0.5f, g_pFramework->getScreenHeight() * 0.33f);

	m_pQuitButton = new LButton(2, "assets/quit_button.png");
	m_pQuitButton->setPosition(g_pFramework->getScreenWidth() * 0.5f - m_pQuitButton->getButtonTextureWidth() * 0.5f, g_pFramework->getScreenHeight() * 0.66f);

	m_pExitButton = new LButton(2, "assets/x_button_sheet.png");
	m_pExitButton->setPosition(g_pFramework->getScreenWidth() - m_pExitButton->getButtonTextureWidth(), 0);

	//Load main screen end

	return success;
}

void Game::processEvents()
{
	//Event handler
	SDL_Event e;

	int menuChoice = 0;

		//Draw Textures
		m_pExitButton->render();

		if (SDL_PollEvent(&e))
		{
		//	menuChoice = handleVillageButtons(e, menuChoice);
			switch (menuChoice)
			{
			//Play button
			case(1):
			{
				m_bGameRun = true;
			}break;

			//Exit button
			case(3):
			{
				m_bGameRun = false;
			}break;
			}

			if (e.type == SDL_QUIT)
			{
				m_bGameRun = false;
			}
		}
}

int Game::showMainmenu(int selectedScreen)
{
	// Push a single event manually to reset button states when returning to this window
	SDL_Event sdlevent;
	sdlevent.type = SDL_MOUSEBUTTONUP;

	SDL_PushEvent(&sdlevent);

	int menuChoice = 0;

	m_iMainMenu = 0; //Reset flag 

	while (m_iMainMenu == 0)
	{
		//Update Framework
		g_pFramework->Update();

		//Render main screen
		m_pGreyBackgroundTexture->render();

		m_pPlayButton->render();
		m_pQuitButton->render();

		g_pFramework->Render();

		//Event handler
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			menuChoice = handleMainmenuButtons(e, menuChoice);
			switch (menuChoice)
			{
			//Play button
			case(1):
			{
				m_iMainMenu = 1;
				m_bGameRun = true;
				selectedScreen = 2;
				return selectedScreen;
			}break;

			//Quit button
			case(2):
			{
				m_iMainMenu = 1;
				m_bGameRun = false;
				selectedScreen = 3;
				return selectedScreen;
			}break;
			}

			if (e.type == SDL_QUIT)
			{
				m_iMainMenu = 1;
				m_bGameRun = false;
				selectedScreen = 0;
				return selectedScreen;
			}
		}
	}
}

int Game::showGameScreen(int selectedScreen)
{
	// Push a single event manually to reset button states when returning to this window
	SDL_Event sdlevent;
	sdlevent.type = SDL_MOUSEBUTTONUP;

	SDL_PushEvent(&sdlevent);

	int menuChoice = 0;

	m_iMainMenu = 0; //Reset flag 

	//Event handler
	SDL_Event e;

	while (m_iMainMenu == 0)
	{
		//Update and draw buttons
		m_pExitButton->render();

		//Update and draw village
		m_pVillage->update();
		m_pVillage->render();

		g_pFramework->Render();

		while (SDL_PollEvent(&e))
		{
			selectedScreen = 2;
			selectedScreen = handleVillageButtons(e);
			switch (selectedScreen)
			{
				//Play button
			case(1):
			{
				m_iMainMenu = 1;
			}break;

			//Quit button
			case(2):
			{
				m_iMainMenu = 2;
			}break;
			//Quit button
			case(3):
			{
				m_iMainMenu = 3;
			}break;
			}
		}
	}
	
	return selectedScreen;
}

int Game::handleMainmenuButtons(SDL_Event e, int choice)
{
	choice = m_pPlayButton->handleEvent(&e, choice);
	choice = m_pQuitButton->handleEvent(&e, choice);
	return choice;
}

int Game::handleVillageButtons(SDL_Event e)
{
	selectedScreen = m_pExitButton->handleEvent(&e, selectedScreen);

	return selectedScreen;
}