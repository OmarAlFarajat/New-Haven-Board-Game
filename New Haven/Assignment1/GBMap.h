#pragma once
#include "Graph.h"

class GBMap 
{
public:
	Graph* mapGraph;
	Graph* tileGraph;
	Graph* resourceGraph; 
	GBMap();
	~GBMap();
};





