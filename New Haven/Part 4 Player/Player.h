#pragma once
#include <iostream>
#include "Deck.h"

class Player
{
public:
	//Player(int playerNum);
	//~Player();
	void PlaceHarvestTile();
	void DrawBuilding();
	void DrawHarvestTile(); //TODO: possible parameters after having the resources implemented(std::shared_ptr<Deck> deck, int slotIndex, int price);
	void ResourceTracker();
	void BuildVillage();

	int getPlayerNumber() 
	{ 
		return playerNumber; 
	}

	int CalculateResources();

private:

	int playerNumber;

};

