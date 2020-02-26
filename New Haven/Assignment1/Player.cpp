#include <iostream>
#include "Player.h"

Player::Player()
{
	this->name = new std::string("Mike");
	this->mine = new Hand;
    this->tracker = mine->getGenerated();
}

Player::~Player()
{
}

void Player::PlaceHarvestTile(GBMap* gb_map)
{
	this->mine->playHarvest(gb_map);
	this->tracker = mine->getGenerated();
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
	//Printing out the Resources
	std::cout << "\nGenerated Resources:" << std::endl;
	std::cout << "SHEEP: " << tracker[0][ResourceType::SHEEP] << std::endl;
	std::cout << "STONE: " << tracker[0][ResourceType::STONE] << std::endl;
	std::cout << "TIMBER: " << tracker[0][ResourceType::TIMBER] << std::endl;
	std::cout << "WHEAT: " << tracker[0][ResourceType::WHEAT] << std::endl;
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
