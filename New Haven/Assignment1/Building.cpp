#include<algorithm>
#include <vector>
#include "Building.h"
#include <time.h>
BuildingTile::BuildingTile()
{
	//Not gonna be used
}

BuildingTile::BuildingTile(ResourceType type, int value)
{
	this->value = new int(value);
	this->type = new ResourceType(type); 
	this->faceUp = new bool(true);
}

BuildingTile::~BuildingTile()
{
}

ResourceType* BuildingTile::getBuildingType()
{
	return this->type;
}

std::string BuildingTile::typeToString()
{
	std::string output;
	switch (*(this->type)) {
	case ResourceType::TIMBER:
		output = "TIMBER";
		break;
	case ResourceType::SHEEP:
		output = "SHEEP";
		break;
	case ResourceType::STONE:
		output = "STONE";
		break;
	case ResourceType::WHEAT:
		output = "WHEAT";
		break;
	default:
		output = "INVALID";
	}
	return output;
}

BuildingDeck::BuildingDeck()
{ 
	std::vector<ResourceType> typeLib = {
		ResourceType::SHEEP,
		ResourceType::STONE,
		ResourceType::TIMBER,
		ResourceType::WHEAT
	};

	/*
	Create a pointer of iterator type for building type
	Loop one color in colorLib one at a time
	Assign a value in range 1 -> 6 for each tile
	There are 36 tiles of one color (6 rows)
	There are 4 colors
	=> 36 * 4 = 144 tiles in the deck
	*/
	
	for(ResourceType x : typeLib)
	for (std::vector<ResourceType>::iterator typeIT = typeLib.begin(); typeIT != typeLib.end(); ++typeIT) {
		int row = 1;
		while (row <= 6) {
			for (int value = 1; value <= 6; ++value) {
				BuildingTile newTile(*typeIT, value);
				this->deck.push_back(newTile);
			}
			row++;
		}
	}
	std::random_shuffle(deck.begin(), deck.end()); //random shuffle the deck
	tileIndex = new int(numOfTiles);
}

BuildingDeck::~BuildingDeck()
{
}

// Draw a tile out of the deck
BuildingTile* BuildingDeck::draw()
{
	if (*tileIndex >= 0) {
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];
	}
	else {
		return NULL;
	}

}

//Override operator to print out the details of building tile
std::ostream& operator<<(std::ostream& os, BuildingTile& bt)
{
	std::string type = bt.typeToString();
	int value = bt.getValue();
	os << "Details of Building Tile:" << std::endl;
	os << "+ Type: " << type << std::endl;
	os << "+ Value: " << *bt.value << std::endl;

	return os;
}
