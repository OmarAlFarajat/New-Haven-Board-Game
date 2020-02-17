#pragma once
#include <vector>
#include "Resources.h"


// Harvest tile class (extends Node)
class HarvestTile
{
public:
	HarvestTile();
	HarvestTile(Resource[4]);
	~HarvestTile();

private:
	const int numOfResource = 4;
	std::vector<Resource> container;
};

/////////////
// TO-DO ... 
//
// The Deck of Harvest Tiles Object
class HarvestDeck
{
public:
	HarvestDeck();
	~HarvestDeck();
	HarvestTile* draw();

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles
	static int *tileIndex;  // keep track of the number of remainning tiles inside the deck to be drawed
	std::vector<HarvestTile> deck;

};