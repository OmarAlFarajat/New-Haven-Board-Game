#pragma once
#include "GBMap.h"

/*
TODO: implement draw() methods in HarvestDeck and BuildingDesk. Let's User use these methods
to draw a tiles (building or harvest)
*/

// Resource class (extends Node)
enum class ResourceType { TIMBER, STONE, WHEAT, SHEEP };

class Resource : public Node
{
public:
	Resource();
	~Resource();
	void setType(ResourceType type);
private:
	ResourceType* type;
};

