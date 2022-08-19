#pragma once
#include "Building.h"

class Village : public Building
{
public:
	Village();
	~Village();

	void checkStorage();
	void update();
	void render();

	void DebugWindow();

	void handleButtons();

private:
	std::string name;
	float ress_wood;
	float ress_iron;
	float ress_clay;
	float wood_per_tick;
	float iron_per_tick;
	float clay_per_tick;
	float storage;

	//Textures
	LTexture* m_pVillageNameTexture;
	LTexture* m_pWoodTextTexture;
	LTexture* m_pIronTextTexture;
	LTexture* m_pClayTextTexture;
	LTexture* m_pBackgroundTexture;

	LTexture* m_pDebugTexture;

	Building* m_pMainBuilding;
};

