#include "Resources.h"
#include "GBMap.h"

Resource::Resource() : Node()
{
}

Resource::~Resource()
{
}

void Resource::setType(ResourceType type) {
	*this->type = type; 
}

