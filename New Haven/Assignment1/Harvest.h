#pragma once
#include <vector>
#include <iostream>
#include "Resources.h"

using std::vector;
using std::ostream;

// Harvest tile class (extends Node)
class HarvestTile
{
public:
	HarvestTile();
	HarvestTile(ResourceType[4]);
	~HarvestTile();
	friend ostream& operator<<(ostream& os, HarvestTile& ht);
	vector<ResourceType> getResources() { return container; }
	vector<ResourceType>* getContainer() { return &container; } // Return a reference to the container

private:
	const int numOfResource = 4;
	vector<ResourceType> container;
};

// The Deck of Harvest Tiles Object
class HarvestDeck
{
public:
	HarvestDeck();
	~HarvestDeck();
	HarvestTile* draw();
	int getNumOfRemain() const; // get the number of remaining card

private:
	const static int numOfTiles = 60; // 60 Harvest Tiles in a Deck
	int *tileIndex;  // keep track of the number of remainning tiles inside the deck to be drawed
	vector<HarvestTile> deck;

};