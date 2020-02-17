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

std::string Resource::getTypeAsString()
{
	std::string str = "";

	switch (*this->type) {
	case ResourceType::WHEAT:
		str = "WHEAT";
		break;
	case ResourceType::TIMBER:
		str = "TIMBER";
		break;
	case ResourceType::STONE:
		str = "STONE";
		break;
	case ResourceType::SHEEP:
		str = "SHEEP";
		break;
	case ResourceType::NONE:
		str = "NONE";
		break;
	}
	return str;

}

