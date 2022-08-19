#pragma once
#include "LButton.h"

enum BuildingType
{
	MAIN_BUILDING = 0,
	BUILDING_TYPES_TOTAL = 1
};

class Building : public LButton
{
public:
	Building();
	~Building();

	void setPosition(int x, int y);
	void render();
	int handleEvent(int currentState);

	Building(int type, int x_pos, int y_pos);
	
private:

	LButton* m_pBuildingButton;
};

