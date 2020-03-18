#pragma once
#include <vector>
#include <iostream>
#include "Resources.h"

using std::vector;
using std::ostream;

// Harvest tile class (extends Node)
class HarvestTile
{
	const int numOfResource = 4;
	vector<ResourceType> container;

public:
	HarvestTile();
	HarvestTile(ResourceType[4]);
	~HarvestTile();

	friend ostream& operator<<(ostream& os, HarvestTile& ht);
	vector<ResourceType> getContainer();
	vector<ResourceType>* getContainerPointer();

};
inline vector<ResourceType> HarvestTile::getContainer() { return container; }
inline vector<ResourceType>* HarvestTile::getContainerPointer() { return &container; } 

// The Deck of Harvest Tiles Object
class HarvestDeck
{
	const static int numOfTiles = 60; 
	int *tileIndex;  
	vector<HarvestTile> deck;

public:
	HarvestDeck();
	~HarvestDeck();


	HarvestTile* draw();
	int getNumOfRemain() const; 

};
inline int HarvestDeck::getNumOfRemain() const {return *tileIndex;}