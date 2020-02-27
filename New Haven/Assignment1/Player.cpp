#include <iostream>
#include "Player.h"

Player::Player()
{
	this->name = new std::string("Mike");
	this->mine = new Hand;
}

Player::~Player()
{
}

void Player::PlaceHarvestTile(GBMap* gb_map)
{
	this->mine->playHarvest(gb_map);
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
