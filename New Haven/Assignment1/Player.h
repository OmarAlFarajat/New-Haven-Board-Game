#pragma once
#include <map>
#include <string>
#include "GBMap.h"
#include "Building.h"
#include "Hand.h"
#include "Resources.h"

class Player {
public:
	Player();
	~Player();

	void PlaceHarvestTile(GBMap* gb_map);
	void DrawBuilding(BuildingDeck* deck);
	void DrawHarvestTile(HarvestDeck* deck);
	
	void ResourceTracker(std::map<ResourceType, int> accumulation);
	void BuildVillage();
	void CalculateResources();

	void show();
private:
	Hand* mine;
	std::string* name;
	std::map<ResourceType, int> tracker;
	/*
	Player own a VG board
	*/

};