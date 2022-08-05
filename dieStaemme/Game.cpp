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

	//Init test village
	m_pVillage = new Village;

	//Mainloop

	while (m_bGameRun == true)
	{
		switch (selectedScreen)
		{
		case 1:
			//selectedScreen = showMainmenu(selectedScreen);
			showMainmenu(selectedScreen);
			break;
		case 2:
			//selectedScreen = showGameScreen(selectedScreen);
			showGameScreen(selectedScreen);
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

	m_pPlayButton = new LButton(2, "assets/play_button.png");
	m_pPlayButton->setPosition(g_pFramework->getScreenWidth() * 0.5f - m_pPlayButton->getButtonTextureWidth() * 0.5f, g_pFramework->getScreenHeight() * 0.33f);

	m_pQuitButton = new LButton(0, "assets/quit_button.png");
	m_pQuitButton->setPosition(g_pFramework->getScreenWidth() * 0.5f - m_pQuitButton->getButtonTextureWidth() * 0.5f, g_pFramework->getScreenHeight() * 0.66f);

	m_pExitButton = new LButton(1, "assets/x_button_sheet.png");
	m_pExitButton->setPosition(g_pFramework->getScreenWidth() - m_pExitButton->getButtonTextureWidth(), 0);

	//Load main screen end

	return success;
}

void Game::processEvents()
{
	int menuChoice = 0;

		if (SDL_PollEvent(&g_pFramework->globalEvent))
		{
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

			if (g_pFramework->globalEvent.type == SDL_QUIT)
			{
				m_bGameRun = false;
			}
		}
}

void Game::showMainmenu(int selectedScreen)
{
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

		handleMainMenu();
	}
}

int Game::showGameScreen(int selectedScreen)
{
	m_iGameScreen = 0; //Reset flag 

	while (m_iGameScreen == 0)
	{
		//Update Framework
		g_pFramework->Update();

		//Update and draw buttons
		m_pExitButton->render();

		//Update and draw village
		m_pVillage->update();
		m_pVillage->render();

		g_pFramework->Render();


		selectedScreen = 2;
		selectedScreen = handleVillageButtons();
		switch (selectedScreen)
		{
			//Play button
		case(1):
		{
			m_iGameScreen = 1;
			menuChoice = 1;
		}break;

		//Quit button
		case(2):
		{
			m_iGameScreen = 2;
		}break;
		//Quit button
		case(3):
		{
			m_iGameScreen = 3;
		}break;
		}
		if (g_pFramework->globalEvent.type == SDL_QUIT)
		{
			m_bGameRun = false;
			selectedScreen = 0;
			return selectedScreen;
		}
	}
	
	return selectedScreen;
}

void Game::handleMainmenuButtons()
{
	menuChoice = m_pPlayButton->handleEvent(selectedScreen);
	selectedScreen = menuChoice; //Update selectedScreen if button was pressed

	menuChoice = m_pQuitButton->handleEvent(selectedScreen);
	selectedScreen = menuChoice;//Update selectedScreen if button was pressed
}

int Game::handleVillageButtons()
{
	selectedScreen = m_pExitButton->handleEvent(selectedScreen);

	return selectedScreen;
}

void Game::handleMainMenu()
{
	while (SDL_PollEvent(&g_pFramework->globalEvent))
	{
		handleMainmenuButtons();
		switch (menuChoice)
		{
			//Play button
		case(1):
		{
			m_iMainMenu = 1;
			m_bGameRun = true;
			selectedScreen = 1;
		}break;

		//X Button button
		case(2):
		{
			m_iMainMenu = 1;
			m_bGameRun = true;
			selectedScreen = 2;
		}break;

		//Quit button
		case(0):
		{
			printf("Button integer was 0, process ended.\n");
			m_iMainMenu = 1;
			m_bGameRun = false;
			selectedScreen = 1;
		}break;
		}

		if (g_pFramework->globalEvent.type == SDL_QUIT)
		{
			m_iMainMenu = 1;
			m_bGameRun = false;
		}
	}
}