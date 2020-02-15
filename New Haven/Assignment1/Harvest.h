#pragma once
#include "Resources.h"

// Harvest tile class (extends Node)
class HarvestTile
{
public:
	HarvestTile();
	HarvestTile(Resource[4]);
	~HarvestTile();

private:
	Resource* resources[4];
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
	HarvestTile draw();

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles
	static int numOfRemain;
	static HarvestTile deck[numOfTiles];

};