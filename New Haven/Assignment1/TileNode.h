#pragma once
#include "Resources.h"
#include "Building.h"
#include <cstddef>

class TileNode : public Node
{
	Resource* resources[4];
	BuildingTile* building;

public:
	TileNode();
	~TileNode();

	// Setter(s)
	void linkResourceNode(Resource* resource, int index);

	// Getter(s)
	Resource** getResourceNodes();
};
inline Resource** TileNode::getResourceNodes() { return resources; }

