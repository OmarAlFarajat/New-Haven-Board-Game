#include "Player.h"
#include <iostream>
#include <string>

int Player::playerCount = 0; // Total number of players that are playing the game

// Default constructor for player arrays
Player::Player()
{
	this->name = "Player"; //set the name of the player

	playerCount++; // Increment the total number of players in the game
	playerNumber = playerCount; // Set the number of players to the current player count


}

Player::Player(std::string name, int playerNumber)
{
	this->name = "Player"; //set the name of the player

	playerCount++; //increment the number of players in the game
	playerNumber = playerCount; //set the player number to the current player count
}

Player::~Player() 	// Class destructor
{
	//make sure the tiles object is deleted
	//delete tiles;
	//tiles = NULL;
	//delete building;
	//building = NULL;
}

std::string Player::getName()
{
	return name;
}

void Player::setName(std::string name)
{
	this->name = name;
}

int Player::getPlayerNumber()
{
	return playerNumber;
}

void Player::setPlayerNumber(int number)
{
	// only allows up to 3 players so between 0 and 3
	if (number >= 0 && number <= 3)
	{
		playerNumber = number;
	}
}

void Player::PlaceHarvestTile()
{
	return;
}

void Player::DrawBuilding()
{

}

void Player::ResourceTracker()
{

}

void Player::BuildVillage()
{

}

//int Player::CalculateResources()
//{
//	//TODO return resources size. waiting for resources to be implemented
//	//return resources.size();
//}
