#pragma once
#include <string>
#include "GBMap.h"

/*
TODO: implement draw() methods in HarvestDeck and BuildingDesk. Let's User use these methods
to draw a tiles (building or harvest)
*/

// Resource class (extends Node)
enum class ResourceType {BEGIN, TIMBER, STONE, WHEAT, SHEEP, NONE, END };
ResourceType& operator++(ResourceType& e) {
	if (e == ResourceType::NONE) {
		throw std::out_of_range("Iterated out of range in ResourceType");
	}
	e = ResourceType(static_cast<std::underlying_type<ResourceType>::type>(e) + 1);
	return e;
}

class Resource : public Node
{
	ResourceType* type;
public:
	Resource();
	~Resource();
	void setType(ResourceType type) {
		*this->type = type;
	}
	ResourceType getType() { return *type; }

	std::string getTypeAsString() { 
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
};


