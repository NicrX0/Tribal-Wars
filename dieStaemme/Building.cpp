#include "Building.h"

Building::Building()
{
	m_Level = 0;
}

Building::~Building()
{

}

Building::Building(int type)
{
	//Get building name
	switch (type)
	{
	case 0:
		m_name = "Main building";
		break;
	default:
		printf("Error could not initialize building name. (Wrong type?)\n");
		break;
	}


	//Initialize building parameter
	m_Level = 1;

	//Set isClicked flag to false
	isClicked = false;

	//Create and load building texture
	m_pBuildingButton = new LButton(1, 11, "assets/village/main_building_new.png");
	m_pBuildingButton->setPosition(g_pFramework->getBottomViewportX_Base() + (g_pFramework->getBottomViewportWidth() / 2), g_pFramework->getBottomViewportY_Base());

	//Set viewport to render to
	g_pFramework->setBuildingMenuViewport();
	//Initialize building name texture
	m_pBuildingNameTexture = new LTexture;

	//Set textcolor black
	SDL_Color textColor = { 0, 0, 0 };
	if (!m_pBuildingNameTexture->loadFromRenderedText(m_name, textColor))
	{
		printf("Failed to render m_pBuildingNameTexture in Building.cpp!\n");
	}
	m_pBuildingNameTexture->SetPos((g_pFramework->currentViewportRect.w / 2) - (m_pBuildingNameTexture->getWidth() / 2), g_pFramework->currentViewportRect.h * 0.006f);

	m_pBuildingMenuTexture = new LTexture;
	if (!m_pBuildingMenuTexture->loadFromFile("assets/village/building_menu.png", g_pFramework->GetRenderer()))
	{
		printf("Error loading building_menu.png\n");
	}
	m_pBuildingMenuTexture->SetPos(5, 0);

	m_pBuildingLevelTexture = new LTexture;
	if (!m_pBuildingLevelTexture->loadFromRenderedText("Level: " + std::to_string(m_Level), textColor))
	{
		printf("Failed to render m_pBuildingMenuTexture in Building.cpp!\n");
	}
	m_pBuildingLevelTexture->SetPos((g_pFramework->currentViewportRect.w * 0.025f), g_pFramework->currentViewportRect.h * 0.10f);
}

void Building::setPosition(int x, int y)
{
	//Show current button sprite
	m_pBuildingButton->setPosition(x, y);
}

void Building::render()
{
	//Show current button sprite
	//m_pBuildingButton->getButtonCoords();
	m_pBuildingButton->renderBuilding();
}

int Building::handleEvent(int currentState)
{
	m_pBuildingButton->handleEvent(currentState);
	if (m_pBuildingButton->buttonState())
	{
		isClicked = true;
	}
	else if (!m_pBuildingButton->buttonState())
	{
		isClicked = false;
	}

	renderBuildingOverlay();

	return currentState;
}

void Building::renderBuildingOverlay()
{
	if (checkClickState())
	{
		//Set viewport to render to
		g_pFramework->setBuildingMenuViewport();
		m_pBuildingMenuTexture->rendertest();
		m_pBuildingNameTexture->render();
		m_pBuildingLevelTexture->render();
	}
}