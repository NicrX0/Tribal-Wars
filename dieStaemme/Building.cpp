#include "Building.h"

Building::Building()
{

}

Building::~Building()
{

}

Building::Building(int type, int x_pos, int y_pos)
{
	//Create and load building texture
	m_pBuildingButton = new LButton(1, 11, "assets/village/main_building_new.png");
	m_pBuildingButton->setPosition(x_pos, y_pos);
}

void Building::setPosition(int x, int y)
{
	//Show current button sprite
	m_pBuildingButton->setPosition(x, y);
}

void Building::render()
{
	//Show current button sprite
	m_pBuildingButton->renderBuilding();
}

int Building::handleEvent(int currentState)
{
	//Show current button sprite
	m_pBuildingButton->handleEvent(currentState);

	return currentState;
}