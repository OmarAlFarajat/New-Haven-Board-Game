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
	Hand* myHand;
	string* name;
	VGMap* vg_map; 
	int* score;

public:
	Player(string name, int vgmap_id);
	~Player();

	bool PlaceShipmentTile(GBMap* gb_map);
	void PlaceHarvestTile(GBMap* gb_map);
	void PlaceBuildingTile(VGMap* vg_map, GBMap* gb_map);
	void setScore(int gainedPoint);

	void DrawShipment(HarvestDeck* deck);
	void DrawBuilding(BuildingDeck* deck);
	void DrawHarvestTile(HarvestDeck* deck);

	void UncoverShipment(GBMap* gb_map);
	bool hasShipmentTile();
	Hand* getHand();
	VGMap* getVGMap();
	string* getName();
	int getScore();
	void show();
  
};
inline void Player::setScore(int gainedPoint) { score = new int(gainedPoint); }
inline bool Player::hasShipmentTile() { return (this->getHand()->hasSHIPMENT_TILE()); }
inline VGMap* Player::getVGMap() {	return vg_map; }
inline Hand* Player::getHand() { return myHand; }
inline string* Player::getName() { return name; }
inline int Player::getScore() { return *score; }

