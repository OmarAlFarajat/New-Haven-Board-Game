#pragma once
#include <vector>
#include <map>
#include "Graph.h"
#include "TileNode.h"

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
};


