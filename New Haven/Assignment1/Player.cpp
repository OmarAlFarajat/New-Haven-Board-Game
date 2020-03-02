#include <iostream>
#include "Player.h"
#include "VGMapLoader.h"

Player::Player()
{
	name = new std::string("Mike");
	mine = new Hand;
	vg_map = new VGMap();
	std::string vgMapName = "Stratford_example.vgmap";
	loadVGMap(vgMapName, *vg_map);

}

Player::~Player()
{
	vg_map = nullptr;
	mine = nullptr;
	name = nullptr;
	delete vg_map;
	delete mine;
	delete name;
}

void Player::PlaceHarvestTile(GBMap* gb_map)
{
	this->mine->playHarvest(gb_map);
}

void Player::PlaceBuildingTile(VGMap* vg_map)
{
	this->mine->playBuilding(vg_map);
}

void Player::DrawBuilding(BuildingDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		std::cout << "There is no more Building Tile in the Deck to draw" << std::endl;
	}
	else {
		mine->addBuildingTile(deck->draw());
	}
}

void Player::DrawHarvestTile(HarvestDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		std::cout << "There is no more Harvest Tile in the Deck to draw" << std::endl;
	} 
	else {
		mine->addHarvestTile(deck->draw());
	}
}

void Player::ResourceTracker()
{

}

void Player::BuildVillage()
{
}

void Player::CalculateResources()
{
}

void Player::show()
{
	// Showing Hand
	this->mine->showHand();
}
