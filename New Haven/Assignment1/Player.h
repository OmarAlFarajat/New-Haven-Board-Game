#pragma once
#include <map>
#include <string>
#include "GBMap.h"
#include "Building.h"
#include "Hand.h"
#include "Resources.h"
#include "VGMap.h"

class Player {
    Hand* myHand;
	std::string* name;
	VGMap* vg_map; 

public:
	Player();
	~Player();

	void PlaceHarvestTile(GBMap* gb_map);
	void PlaceBuildingTile(VGMap* vg_map);

	void DrawBuilding(BuildingDeck* deck);
	void DrawHarvestTile(HarvestDeck* deck);

	VGMap* getVGMap();

	void show();
};
inline VGMap* Player::getVGMap() {	return vg_map; }
