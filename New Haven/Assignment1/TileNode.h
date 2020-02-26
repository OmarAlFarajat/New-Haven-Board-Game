#pragma once
#include "Resources.h"
#include <cstddef>

class TileNode : public Node
{
	Resource* resources[4];
public:
	TileNode();
	~TileNode();
	void linkResourceNode(Resource* resource, int index);
	Resource** getResourceNodes();
};

