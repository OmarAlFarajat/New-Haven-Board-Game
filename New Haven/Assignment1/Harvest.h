#pragma once
#include <vector>
#include <iostream>
#include "Resources.h"

// Harvest tile class (extends Node)
class HarvestTile
{
	const int numOfResource = 4;
	std::vector<ResourceType> container;

public:
	HarvestTile();
	HarvestTile(ResourceType[4]);
	~HarvestTile();

	friend std::ostream& operator<<(std::ostream& os, HarvestTile& ht);
	std::vector<ResourceType> getContainer();
	std::vector<ResourceType>* getContainerPointer();

};
inline std::vector<ResourceType> HarvestTile::getContainer() { return container; }
inline std::vector<ResourceType>* HarvestTile::getContainerPointer() { return &container; } 

// The Deck of Harvest Tiles Object
class HarvestDeck
{
	const static int numOfTiles = 60; 
	int *tileIndex;  
	std::vector<HarvestTile> deck;

public:
	HarvestDeck();
	~HarvestDeck();

	HarvestTile* draw();
	int getNumOfRemain() const; 

};
inline int HarvestDeck::getNumOfRemain() const {return *tileIndex;}