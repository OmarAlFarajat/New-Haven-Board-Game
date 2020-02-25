#include "TileNode.h"

TileNode::TileNode()
{
	resources[0] = NULL;
	resources[1] = NULL;
	resources[2] = NULL;
	resources[3] = NULL;

}

TileNode::~TileNode()
{
}

void TileNode::linkResourceNode(Resource* resource, int index)
{
	
	resources[index] = resource; 
}

Resource** TileNode::getResourceNodes() { return resources; }


