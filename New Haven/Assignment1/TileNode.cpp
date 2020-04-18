#include "TileNode.h"

// TODO: Consider making all of this header-only? 

TileNode::TileNode()
{
	resources[0] = nullptr;
	resources[1] = nullptr;
	resources[2] = nullptr;
	resources[3] = nullptr;
	building = new BuildingTile();
}

TileNode::~TileNode()
{
}

void TileNode::linkResourceNode(Resource* resource, int index)
{
	resources[index] = resource; 
}



