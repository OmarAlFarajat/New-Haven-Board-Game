#include "GBMap.h"

GBMap::GBMap()
{
	mapGraph = new Graph();
	tileGraph = new Graph();
	resourceGraph = new Graph(); 
}

GBMap::~GBMap()
{
}
