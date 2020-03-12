#pragma once
#include <string>
#include "Node.h"

enum class ResourceType {TIMBER, STONE, WHEAT, SHEEP, NONE};

// Resource class (extends Node)
class Resource : public Node
{
	ResourceType* type;

public:
	Resource();
	~Resource();
	void setType(ResourceType type);
	ResourceType getType();
	std::string getTypeAsString();
};

inline void Resource::setType(ResourceType type) { *this->type = type; }
inline ResourceType Resource::getType() { return *type; }

