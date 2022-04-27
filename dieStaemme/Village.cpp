#include "Village.h"

Village::Village()
{
	name = "Default";
	storage = 205.0f;
	ress_wood = 200.0f;
	ress_iron = 200.0f;
	ress_clay = 200.0f;
	wood_per_tick = 1.0f;
	iron_per_tick = 1.0f;
	clay_per_tick = 1.0f;


	//Load background texture
	m_pBackgroundTexture = new LTexture;
	if (!m_pBackgroundTexture->loadFromFile("assets/game_background.png", g_pFramework->GetRenderer()))
	{
		printf("Error loading game_background.png\n");
	}

	//Load village name texture
	m_pVillageNameTexture = new LTexture;

	//Buildings
	m_pMainBuildingTexture = new Building(MAIN_BUILDING);
	m_pMainBuildingTexture->setPosition(g_pFramework->getScreenWidth() / 2 - m_pMainBuildingTexture->getBuildingTextureWidth() / 2, g_pFramework->getScreenHeight() * 0.66f);

	//Set textcolor black
	SDL_Color textColor = { 0, 0, 0 };

	if (!m_pVillageNameTexture->loadFromRenderedText("Village: " + name, textColor))
	{
		printf("Failed to render village name text texture!\n");
	}

	//Create text texture
	m_pWoodTextTexture = new LTexture;
	m_pIronTextTexture = new LTexture;
	m_pClayTextTexture = new LTexture;
}

Village::~Village()
{
	m_pVillageNameTexture->free();
	m_pWoodTextTexture->free();
	m_pIronTextTexture->free();
	m_pClayTextTexture->free();
	m_pBackgroundTexture->free();
}

void Village::checkStorage()
{
	if (ress_wood > storage) { ress_wood = storage; }
	if (ress_iron > storage) { ress_iron = storage; }
	if (ress_clay > storage) { ress_clay = storage; }
}

void Village::update()
{
	//Update ressources
	ress_wood = ress_wood + (wood_per_tick * g_pTimer->getElapsed());
	ress_iron = ress_iron + (iron_per_tick * g_pTimer->getElapsed());
	ress_clay = ress_clay + (clay_per_tick * g_pTimer->getElapsed());

	//Check if storage is full
	checkStorage();

	//m_pMainBuildingTexture->handleEvent();
}

void Village::render()
{
	//Render background
	m_pBackgroundTexture->render();

	//Set position of village name texture and render to screen
	m_pVillageNameTexture->SetPos(g_pFramework->getScreenWidth() * 0.02f, g_pFramework->getScreenHeight() * 0.01f);
	m_pVillageNameTexture->render();

	//Set textcolor black
	SDL_Color textColor = { 0, 0, 0 };

	//Render text in red instead if storage is full
	if (ress_wood == storage) { textColor = { 255, 0, 0 }; };
	if (!m_pWoodTextTexture->loadFromRenderedText("Wood: " + std::to_string(static_cast<int>(ress_wood)), textColor))
	{
		printf("Failed to render text texture!\n");
	}
	m_pWoodTextTexture->SetPos(g_pFramework->getScreenWidth() * 0.51f, g_pFramework->getScreenHeight() * 0.01f);

	//Reset text color to black if it was changed
	textColor = { 0, 0, 0 };

	//Render text in red instead if storage is full
	if (ress_iron == storage) { textColor = { 255, 0, 0 }; };
	if (!m_pIronTextTexture->loadFromRenderedText("Iron: " + std::to_string(static_cast<int>(ress_iron)), textColor))
	{
		printf("Failed to render text texture!\n");
	}
	m_pIronTextTexture->SetPos(g_pFramework->getScreenWidth() * 0.51f, g_pFramework->getScreenHeight() * 0.1f);

	//Reset text color to black if it was changed
	textColor = { 0, 0, 0 };

	//Render text in red instead if storage is full
	if (ress_clay == storage) { textColor = { 255, 0, 0 }; };
	if (!m_pClayTextTexture->loadFromRenderedText("Clay: " + std::to_string(static_cast<int>(ress_clay)), textColor))
	{
		printf("Failed to render text texture!\n");
	}
	m_pClayTextTexture->SetPos(g_pFramework->getScreenWidth() * 0.51f, g_pFramework->getScreenHeight() * 0.189f);

	m_pWoodTextTexture->render();
	m_pIronTextTexture->render();
	m_pClayTextTexture->render();

	//Render buildings
	m_pMainBuildingTexture->render();
}

void Village::handleButtons()
{

}