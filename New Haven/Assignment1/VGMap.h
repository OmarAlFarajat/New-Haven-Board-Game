#pragma once
#include <string>
#include "Graph.h"
#include "Building.h"

class VGMap
{
	Graph* buildingGraph;
	std::string* name;

public:
	VGMap();
	~VGMap();
	Graph* getBuildingGraph() {	return buildingGraph; }
	bool isValid(BuildingTile* fromHand, BuildingTile* toBoard);
	void placeBuildingTile(BuildingTile* fromHand, BuildingTile* toBoard);
	int calculatePoints(); 
	void initTileValues();
};

