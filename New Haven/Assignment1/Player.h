//#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "../Assignment1/Harvest.h"
#include "../Assignment1/Building.h"

class Player
{
private:
	std::string name; // the player's nickname
	static int playerCount; // Total number of players that are playing the game
	int playerNumber; //Player identifier i.e. player 1, player 2, etc.
	int numOfHarvestTiles;
	int numOfBuildings;
	std::vector<HarvestTile> harvestTiles;
	std::vector<BuildingTile> buildingTiles;

public:
	Player();	// Default constructor
	Player(std::string, int playerNumber);
	~Player();	// Player class destructor

	// Set Methods
	void setName(std::string); //set the name of the player
	void setPlayerNumber(int); //set the number of the player: player1, player2, etc.
	void setNumOfHarvestTiles(int h);
	void setNumOfBuildings(int b);


	// Get Methods
	std::string getName();		//get the name of the player
	int getPlayerNumber(); //get the number of the player: player1,player 2, etc.
	int getNumOfHarvestTiles(void);
	int getNumOfBuildings(void);

	HarvestTile draw();
	//BuildingTiles draw();

	void PlaceHarvestTile();
	void DrawBuilding();
	void ResourceTracker();
	void BuildVillage();

	//int CalculateResources();

};
#endif

