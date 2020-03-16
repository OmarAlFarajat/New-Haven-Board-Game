#pragma once
#include <string>
#include "Graph.h"
#include "Building.h"

using std::string;

class VGMap
{
	Graph* buildingGraph;
	string* name;

public:
	VGMap();
	~VGMap();

	// Helper to Hand::playBuilding(). Checks if building tile placement is valid.
	bool isValid(BuildingTile* fromHand, BuildingTile* toBoard);

	// Calculates and returns the number of points based on the building placement on the VGMap
	int calculatePoints();

	// Setters
	void setName(std::string name) { *this->name = name; }
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
	Graph* getBuildingGraph() {	return buildingGraph; }
	std::string getName() { return *name; }


};

