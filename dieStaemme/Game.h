#pragma once
#include "LTexture.h"
#include "Village.h"
#include <iostream>

class Game
{
public:

	Game();

	bool Initialize(SDL_Renderer* renderer);
	void Run();
	void Quit();

	bool loadMedia(SDL_Renderer* renderer);

	//Scenes
	int showMainmenu(int selectedScreen);
	int handleMainMenu();

	int showGameScreen(int selectedScreen);

	void handleMainmenuButtons();
	void handleVillageButtons();
	void DebugWindow();

private:
	SDL_Window* gWindow;

	int m_iMainMenu;
	int m_iGameScreen;

	//test
	int menuChoice;

	bool m_bGameRun;
	int selectedScreen;

	//Textures
	LTexture* m_pGreyBackgroundTexture;
	LTexture* m_pXButtonTexture;
	LTexture* m_pTextTexture;
	LTexture* m_pBackgroundTexture;
	LTexture* m_pHouse0Texture;
	LTexture* m_pHouse1Texture;

	//Debug info textures
	LTexture* m_pDebugTexture;
	LTexture* m_pMouseXPosTexture;
	LTexture* m_pMouseYPosTexture;

	//Village
	Village* m_pVillage;

	//Buttons
	LButton* m_pButton[1];
	LButton* m_pExitButton;
	LButton* m_pPlayButton;
	LButton* m_pQuitButton;
};
