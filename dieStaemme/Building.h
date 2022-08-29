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
	std::string getBuildingName() { return m_name; }

	Building(int type);

	bool checkClickState() { return isClicked; }
	
private:

	int m_Level;
	std::string m_name;

	LButton* m_pBuildingButton;

	bool isClicked;
};

