#pragma once
#include <vector>
#include <map>
#include "Graph.h"
#include "TileNode.h"
#include "Harvest.h"

class GBMap 
{
	Graph* tileGraph;
	Graph* resourceGraph;
public:
	GBMap();
	~GBMap();
	Graph* getTileGraph() { return tileGraph; }
	Graph* getResourceGraph() { return resourceGraph; }
	void calcResourceAdjacencies(TileNode* root, std::map<ResourceType, int> & output);
	bool isValid(TileNode* tileNode);
	bool placeHarvestTile(HarvestTile* harvestTile, TileNode* tileNode);
};


