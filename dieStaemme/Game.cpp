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

	//Init test village
	m_pVillage = new Village;

	m_pDebugTexture = new LTexture;
	m_pDebugTexture->SetPos(g_pFramework->getScreenWidth() * 0.02f, g_pFramework->getScreenHeight() * 0.2f);

	return success;
}

void Game::Run()
{
	//Keyboard handler
	KeyboardHandler keyboard;

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

		//Show TPS
		DebugWindow();

		//Update screen
		g_pFramework->Render();

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

int Game::showMainmenu(int selectedScreen)
{
		//Render main screen
		m_pGreyBackgroundTexture->render();

		m_pPlayButton->render();
		m_pQuitButton->render();

		selectedScreen = handleMainMenu();

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

		return selectedScreen;
}

int Game::showGameScreen(int selectedScreen)
{
		//Draw buttons
		m_pExitButton->render();

		//Update village
		m_pVillage->update();
		m_pVillage->render();

			handleVillageButtons();

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

	return selectedScreen;
}

void Game::handleMainmenuButtons()
{
	selectedScreen = m_pPlayButton->handleEvent(selectedScreen);

	selectedScreen = m_pQuitButton->handleEvent(selectedScreen);
}

void Game::handleVillageButtons()
{
	selectedScreen = m_pExitButton->handleEvent(selectedScreen);
}

int Game::handleMainMenu()
{
		handleMainmenuButtons();
		switch (selectedScreen)
		{
			//Play button
		case(1):
		{
			m_iMainMenu = 1;
			m_bGameRun = true;
			return selectedScreen;
		}break;

		//X Button button
		case(2):
		{
			m_iMainMenu = 1;
			m_bGameRun = true;
			return selectedScreen;
		}break;

		//Quit button
		case(0):
		{
			printf("Button integer was 0, process ended.\n");
			m_iMainMenu = 1;
			m_bGameRun = false;
			return selectedScreen;
		}break;
		}

		if (g_pFramework->globalEvent.type == SDL_QUIT)
		{
			m_iMainMenu = 1;
			m_bGameRun = false;
			return selectedScreen;
		}
}

void Game::DebugWindow()
{
	//Set textcolor black
	SDL_Color textColor = { 0, 0, 0 };

	if (!m_pDebugTexture->loadFromRenderedText("TPS: " + std::to_string(g_pFramework->getTPS()), textColor))
	{
		printf("Failed to render DebugWindow in Village!\n");
	}

	m_pDebugTexture->render();
}