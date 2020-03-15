#include <iostream>
#include "Player.h"
#include "VGMapLoader.h"

using std::cout;
using std::endl;

Player::Player()
{
	name = new string("Mike");
	mine = new Hand;
	vg_map = new VGMap();
	string vgMapName = "Stratford_example.vgmap";
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

/*
The two functions PlaceHarvestTile and PlaceBuildingTile will start a playing session for
the corresponding type.
The two functions were defined inside Hand

The "Player" uses "Hand" to "Place Harvest Tile"
The "Player" uses "Hand" to "Place Building Tile"
*/
void Player::PlaceHarvestTile(GBMap* gb_map)
{
	this->mine->playHarvest(gb_map);
}

void Player::PlaceBuildingTile(VGMap* vg_map)
{
	this->mine->playBuilding(vg_map);
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
		cout << "There is no more Building Tile in the Deck to draw" << std::endl;
	}
	else {
		mine->addBuildingTile(deck->draw());
	}
}

void Player::DrawHarvestTile(HarvestDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		cout << "There is no more Harvest Tile in the Deck to draw" << std::endl;
	} 
	else {
		mine->addHarvestTile(deck->draw());
	}
}

/*
The 3 below methods are not implemented since the team decided to change the design, different from 
the assignment handout.
Instead of tracking resources in Player, the team decided to include the resource trackers in the Gameboard (GBMap)
The decision was rational since the physical board game has the resource trackers on the board.
All related calculating functions were moved to GBMap file.

*/
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
	// Showing all the cards currently on Hand
	this->mine->showHand();
}
