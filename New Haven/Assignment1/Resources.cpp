#include "Resources.h"
#include "GBMap.h"

Resource::Resource() : Node()
{
	type = new ResourceType();
	*type = ResourceType::NONE;
}

Resource::~Resource()
{
}

