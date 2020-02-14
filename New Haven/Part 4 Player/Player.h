#pragma once
#include <iostream>
#include <string>
//#include "Deck.h"

class Player
{
private:
	//static Characters* chosenCharacters; // Array that holds all the characters that have been chosen so far so that no character is played by more than one player
	static int playerCount; // Total number of players that are playing the game
	int playerNumber; //Player identifier i.e. player 1, player 2, etc.
	int player = 0;
	std::string name; // the player's nickname

	void initializeCharacters(); // Method that initializes the chosen characters at the start of the game


public:
	Player();	// Default constructor
	Player(std::string, int playerNumber);
	~Player();	// Player class destructor
	std::string getName();		//get the name of the player
	void setName(std::string); //set the name of the player

	//static enum Characters* getChosenCharacters(); //gets a pointer to an array holding the chosen characters

	void setPlayerNumber(int); //set the number of the player: player1, player2, etc.
	int getPlayerNumber(); //get the number of the player: player1,player 2, etc.

	void PlaceHarvestTile();
	void DrawBuilding();
	void DrawHarvestTile(); //TODO: possible parameters after having the resources implemented (std::shared_ptr<Deck> deck, int slotIndex, int price);
	void ResourceTracker();
	void BuildVillage();

	

	//int CalculateResources();

};

