#pragma once
#include <vector>
#include <iostream>
#include "Resources.h"

using std::vector;
using std::ostream;

// Harvest tile class (extends Node)
class HarvestTile
{
	bool* shipmentTile;
	const int numOfResource = 4;
	vector<ResourceType> container;
	vector<ResourceType*>* shipmentContainer;
	bool* isSelected; 

public:
	HarvestTile();
	HarvestTile(ResourceType[4]);
	~HarvestTile();
	int getNumOfResource();
	friend ostream& operator<<(ostream& os, HarvestTile& ht);
	bool isShipmentTile();
	bool getIsSelected();
	void setIsSelected(bool selected);
	void setShipmentStatus(bool status);
	bool makeShipmentOf(ResourceType type);
	vector<ResourceType> getContainer();
	vector<ResourceType*> getShipmentContainer();
	vector<ResourceType>* getContainerPointer();
};

inline void HarvestTile::setIsSelected(bool selected) { *isSelected = selected; }
inline bool HarvestTile::getIsSelected() { return *isSelected; };
inline int HarvestTile::getNumOfResource() { return numOfResource; }
inline bool HarvestTile::isShipmentTile() { return *shipmentTile; }
inline void HarvestTile::setShipmentStatus(bool status) { *shipmentTile = status; }
inline vector<ResourceType> HarvestTile::getContainer() { return container; }
inline vector<ResourceType*> HarvestTile::getShipmentContainer() { return *shipmentContainer; }
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