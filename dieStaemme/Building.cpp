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

	return currentState;
}