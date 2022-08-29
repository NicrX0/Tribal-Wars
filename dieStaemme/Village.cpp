#include "Village.h"

Village::Village()
{
	name = "Default";
	storage = 300.0f;
	ress_wood = 200.0f;
	ress_iron = 200.0f;
	ress_clay = 200.0f;
	wood_per_tick = 0.0000002f;
	iron_per_tick = 0.0000002f;
	clay_per_tick = 0.0000002f;


	//Load background texture
	m_pBackgroundTexture = new LTexture;
	if (!m_pBackgroundTexture->loadFromFile("assets/game_background.png", g_pFramework->GetRenderer()))
	{
		printf("Error loading game_background.png\n");
	}

	//Load village name texture
	m_pVillageNameTexture = new LTexture;

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

	//Create debug text texture
	m_pDebugTexture = new LTexture;
	m_pDebugTexture->SetPos(g_pFramework->getScreenWidth() * 0.02f, g_pFramework->getScreenHeight() * 0.2f);

	//Buildings
	//Set viewport to render to
	g_pFramework->setBottomViewport();
	m_pMainBuilding = new Building(MAIN_BUILDING);

	//Set viewport to render to
	g_pFramework->setBuildingMenuViewport();
	//Initialize building name texture
	m_pBuildingNameTexture = new LTexture;

	//Set textcolor black
	textColor = { 0, 0, 0 };
	if (!m_pBuildingNameTexture->loadFromRenderedText(m_pMainBuilding->getBuildingName(), textColor))
	{
		printf("Failed to render m_pBuildingNameTexture in Building.cpp!\n");
	}
	m_pBuildingNameTexture->SetPos((g_pFramework->currentViewportRect.w / 2) - (m_pBuildingNameTexture->getWidth() / 2), g_pFramework->currentViewportRect.h * 0.006f);

	//Test
	g_pFramework->setBuildingMenuViewport();
	m_pBuildingMenuTexture = new LTexture;
	if (!m_pBuildingMenuTexture->loadFromFile("assets/village/building_menu.png", g_pFramework->GetRenderer()))
	{
		printf("Error loading building_menu.png\n");
	}
	m_pBuildingMenuTexture->SetPos(5, 0);
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
	ress_wood = ress_wood + (wood_per_tick * g_pFramework->getTPS());
	ress_iron = ress_iron + (iron_per_tick * g_pFramework->getTPS());
	ress_clay = ress_clay + (clay_per_tick * g_pFramework->getTPS());

	//Check if storage is full
	checkStorage();

	//Check for events
	handleButtons();
}

void Village::render()
{
	//------------------------------- RENDER TO FULL SCREEN -------------------------------
	//Set viewport to render to
	g_pFramework->setFullscreenViewport();

	//Render background
	m_pBackgroundTexture->render();

	//------------------------------- RENDER TO TOP SCREEN -------------------------------
	//Set viewport to render to
	g_pFramework->setTopViewport();

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

	//------------------------------- RENDER TO BOTTOM SCREEN -------------------------------
	//Set viewport to render to
	g_pFramework->setBottomViewport();

	//Render buildings
	m_pMainBuilding->render();
}

void Village::handleButtons()
{

	m_pMainBuilding->handleEvent(MAIN_BUILDING);

	if (m_pMainBuilding->checkClickState())
	{
		//Set viewport to render to
		g_pFramework->setBuildingMenuViewport();
		m_pBuildingMenuTexture->rendertest();
		m_pBuildingNameTexture->render();
	}
}