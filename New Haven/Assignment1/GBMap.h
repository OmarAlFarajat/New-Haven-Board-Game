#pragma once
#include <vector>
#include "Graph.h"

class GBMap 
{
public:
	Graph* tileGraph;
	Graph* resourceGraph; 
	GBMap();
	~GBMap();
};


