#include <iostream>
#include "Player.h"
#include "VGMapLoader.h"

using std::cout;
using std::endl;

Player::Player(string name, int vgmap_id)
{
	this->name = new string(name);
	myHand = new Hand;

	vg_map = new VGMap();

	string vgMapName;
	switch (vgmap_id) {
	case 0:
		vgMapName = "./Maps/Stratford.vgmap";
		break;
	case 1:
		vgMapName = "./Maps/Fairfield.vgmap";
		break;
	case 2:
		vgMapName = "./Maps/Guilford.vgmap";
		break;
	case 3:
		vgMapName = "./Maps/Milford.vgmap";
		break;
	default: 
		vgMapName = "./Maps/Stratford.vgmap";
	}

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

bool Player::PlaceShipmentTile(GBMap* gb_map) {
	return this->myHand->playSHIPMENT(gb_map);
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

void Player::PlaceBuildingTile(VGMap* vg_map, GBMap* gb_map)
{
	this->myHand->playBuilding(vg_map, gb_map);
}

void Player::DrawShipment(HarvestDeck* deck) {
	if (deck->getNumOfRemain() <= 0) {
		cout << "There is no harvesr Tile in the Deck";
	}
	else {
		myHand->addSHIPMENT(deck->draw());
	}
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
		cout << "There is no more Building Tile in the Deck to draw" << endl;
	}
	else {
		myHand->addBuildingTile(deck->draw());
	}
}

void Player::DrawHarvestTile(HarvestDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		cout << "There is no more Harvest Tile in the Deck to draw" << endl;
	} 
	else {
		myHand->addHarvestTile(deck->draw());
	}
}

void Player::UncoverShipment(GBMap* gb_map) {
	myHand->uncoverShipment(gb_map);
}

void Player::show()
{
	this->myHand->showHand();
}
