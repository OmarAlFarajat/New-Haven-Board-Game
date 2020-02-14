//#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "../Part 5 Buildings Deck Hand/Resources.h"

class Player
{
private:
	static int playerCount; // Total number of players that are playing the game
	int playerNumber; //Player identifier i.e. player 1, player 2, etc.
	//int player = 0;
	std::string name; // the player's nickname

public:
	Player();	// Default constructor
	Player(std::string, int playerNumber);
	~Player();	// Player class destructor

	// Set Methods
	void setName(std::string); //set the name of the player
	void setPlayerNumber(int); //set the number of the player: player1, player2, etc.


	// Get Methods
	std::string getName();		//get the name of the player
	int getPlayerNumber(); //get the number of the player: player1,player 2, etc.

	HarvestTiles draw();
	//BuildingTiles draw();

	void PlaceHarvestTile();
	void DrawBuilding();
	void ResourceTracker();
	void BuildVillage();

	//int CalculateResources();

};
#endif

