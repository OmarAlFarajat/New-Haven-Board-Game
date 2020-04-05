#pragma once
#include <string>
#include "Graph.h"
#include "Building.h"

using std::string;

class VGMap
{
	Graph* buildingGraph;
	string* name;
	/*
	firstPlacement vector: holds 4 bool values showing 
	which type has been placed on the VGBoard
	The order is: TIMBER, STONE, WHEAT, SHEEP respectively
	*/
	std::vector<bool*>* firstPlacementExisted;

public:
	VGMap();
	~VGMap();

	//Check first placement
	void setFirstPlacement(ResourceType);
	bool isFirstPlacement(ResourceType);
	bool isAdjacent(ResourceType const fromHand, BuildingTile* const onBoard);
	// Helper to Hand::playBuilding(). Checks if building tile placement is valid.
	bool isValid(BuildingTile* fromHand, BuildingTile* toBoard);

	// Calculates and returns the number of points based on the building placement on the VGMap
	int calculatePoints();

	// Setters
	void setName(std::string name);
	/*	Sets the Building "cost" for each building tile in VGMap. 
	*(!)HACK:
	*	initTileValues() is hardcoded assuming that the VGMap is always 5x6.
	*	Having a variable size VGMap isn't neccesary for the game itself.
	*	But, it could be a nice feature to implement for custom games.	*/
	void initTileValues();

	/*	Helper to Hand::PlayBuilding().	
	*	Sets the member data of BuildingTile fromHand to that of toBoard.
	*(!)This behaves like a setter.		*/
	void placeBuildingTile(BuildingTile* fromHand, BuildingTile* toBoard);

	// Getters
	Graph* getBuildingGraph();
	string getName();

};

inline void VGMap::setName(std::string name) { *this->name = name; }
inline Graph* VGMap::getBuildingGraph() {	return buildingGraph; }
inline	string VGMap::getName() { return *name; }
