#pragma once
#include "Resources.h"
#include <cstddef>

class TileNode : public Node
{
	Resource* resources[4];

public:
	TileNode();
	~TileNode();

	// Setter(s)
	void linkResourceNode(Resource* resource, int index);

	// Getter(s)
	Resource** getResourceNodes();
};

