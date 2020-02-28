#pragma once
#include <vector>
#include <map>
#include "Graph.h"
#include "TileNode.h"
#include "Harvest.h"
#include "Building.h"

class GBMap 
{
	Graph* tileGraph;
	Graph* resourceGraph;
	std::map<ResourceType, int>* resourceTracker;
	BuildingTile* buildingsAvailable[5];


public:
	GBMap();
	~GBMap();
	Graph* getTileGraph() { return tileGraph; }
	Graph* getResourceGraph() { return resourceGraph; }
	void setResourceTracker(std::map<ResourceType, int>* inTracker);
	void displayResourceTracker();
	void calcResourceAdjacencies(TileNode* root, std::map<ResourceType, int> & output);
	bool isValid(TileNode* tileNode);
	bool placeHarvestTile(HarvestTile* harvestTile, TileNode* tileNode);
};


