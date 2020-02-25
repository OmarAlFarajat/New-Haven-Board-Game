#pragma once
#include <string>
#include "Graph.h"
class VGMap
{
	Graph* buildingGraph;
	std::string* name;

public:
	VGMap();
	~VGMap();
	Graph* getBuildingGraph() {	return buildingGraph; }
};

