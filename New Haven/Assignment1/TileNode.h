#pragma once
#include "Resources.h"

class TileNode : public Node
{
	Resource* resources[4];
public:
	TileNode();
	~TileNode();
};

