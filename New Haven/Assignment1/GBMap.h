#pragma once
#include <vector>
#include "Graph.h"

class GBMap 
{
	Graph* tileGraph;
	Graph* resourceGraph;
public:
	GBMap();
	~GBMap();
	Graph* getTileGraph() { return tileGraph; }
	Graph* getResourceGraph() { return resourceGraph; }

};


