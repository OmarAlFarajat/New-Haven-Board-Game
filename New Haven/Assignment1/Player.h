#pragma once
#include <map>
#include <string>
#include "GBMap.h"
#include "Building.h"
#include "Hand.h"
#include "Resources.h"
#include "VGMap.h"

using std::string;

class Player {
public:
	Player();
	~Player();

	void PlaceHarvestTile(GBMap* gb_map);
	void PlaceBuildingTile(VGMap* vg_map);
	void DrawBuilding(BuildingDeck* deck);
	void DrawHarvestTile(HarvestDeck* deck);
	VGMap* getVGMap() {	return vg_map; }
	void ResourceTracker();
	void BuildVillage();
	void CalculateResources();

	void show();

private:
    Hand* mine;
	string* name;
	VGMap* vg_map; 

};