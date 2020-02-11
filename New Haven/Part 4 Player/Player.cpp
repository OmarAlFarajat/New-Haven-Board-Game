#include "Player.h"
#include <iostream>
#include <string>

int Player::playerCount = 0; // Total number of players that are playing the game
enum Characters* Player::chosenCharacters = new Characters[3];


// Default constructor for player arrays
Player::Player()
{
	// If playerCount is 0, then initialize the array of chosenCharacters
	if (playerCount == 0)
	{
		Player::initializeCharacters();
	}

	this->name = "Player"; //set the name of the player

	playerCount++; // Increment the total number of players in the game
	playerNumber = playerCount; // Set the number of players to the current player count


}

Player::Player(std::string name, int playerNumber)
{
	//if the playerCount is 0 then initialize the array of chosenCharacters
	if (playerCount == 0)
	{
		Player::initializeCharacters();
	}

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
	delete[] chosenCharacters;
	chosenCharacters = NULL;
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

enum Characters* Player::getChosenCharacters()
{
	return chosenCharacters;
}

void Player::initializeCharacters()
{
	/* Method is only called once, when the player count is zero in the constructor
	it exists to initialize everything in the chosen characters array to something that could not be picked
	*/
	for (int i = 0; i < 3; i++)
	{
		chosenCharacters[i] = 0;
	}
}

void Player::PlaceHarvestTile()
{
	return;
}

void Player::DrawBuilding()
{

}

void Player::DrawHarvestTile()
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
