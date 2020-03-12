#include <iostream>
#include "Player.h"
#include "VGMapLoader.h"

Player::Player()
{
	name = new std::string("Mike");
	myHand = new Hand;
	vg_map = new VGMap();
	std::string vgMapName = "Stratford_example.vgmap";
	loadVGMap(vgMapName, *vg_map);

}

Player::~Player()
{
	vg_map = nullptr;
	myHand = nullptr;
	name = nullptr;
	delete vg_map;
	delete myHand;
	delete name;
}

/*
The two functions PlaceHarvestTile and PlaceBuildingTile will start a playing session for
the corresponding type.
The two functions were defined inside Hand

The "Player" uses "Hand" to "Place Harvest Tile"
The "Player" uses "Hand" to "Place Building Tile"
*/
void Player::PlaceHarvestTile(GBMap* gb_map)
{
	this->myHand->playHarvest(gb_map);
}

void Player::PlaceBuildingTile(VGMap* vg_map)
{
	this->myHand->playBuilding(vg_map);
}

/*
The two functions DrawBuilding and DrawHarvestTile
will call function draw from the player's hand. 
After drawing the card, the functions in hand will put 
the drawn card on hand.
*/
void Player::DrawBuilding(BuildingDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		std::cout << "There is no more Building Tile in the Deck to draw" << std::endl;
	}
	else {
		myHand->addBuildingTile(deck->draw());
	}
}

void Player::DrawHarvestTile(HarvestDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		std::cout << "There is no more Harvest Tile in the Deck to draw" << std::endl;
	} 
	else {
		myHand->addHarvestTile(deck->draw());
	}
}

void Player::show()
{
	this->myHand->showHand();
}
