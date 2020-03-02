#include<algorithm>
#include <vector>
#include "Building.h"

BuildingTile::BuildingTile()
{
	this->value = new int(0);
	this->type = new ResourceType(ResourceType::NONE);
	this->faceUp = new bool(true);
}

BuildingTile::BuildingTile(ResourceType type, int value)
{
	this->value = new int(value);
	this->type = new ResourceType(type); 
	this->faceUp = new bool(true);
}

BuildingTile::~BuildingTile()
{
	value = nullptr;
	type = nullptr;
	faceUp = nullptr;
	delete value;
	delete type;
	delete faceUp;
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
	Loop one color in colorLib one at a time
	Assign a value in range 1 -> 6 for each tile
	There are 36 tiles of one color (6 rows)
	There are 4 colors
	=> 36 * 4 = 144 tiles in the deck
	*/

	int numOfaType = 36;
	for (ResourceType type : typeLib) {
		for(int i = 0; i < numOfaType; ++i) {
			int count = 1;
			while(count <= 6) {
				BuildingTile newTile(type, count);
				this->deck.push_back(newTile);
				count++;
			}
		}
	}

	std::random_shuffle(deck.begin(), deck.end()); //random shuffle the deck
	tileIndex = new int(numOfTiles);
}

BuildingDeck::~BuildingDeck()
{
	tileIndex = nullptr;
	delete tileIndex;
}

// Draw a tile out of the deck
BuildingTile* BuildingDeck::draw()
{
	if (*tileIndex >= 0) {
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];
	}
	else {
		return nullptr;
	}

}

//Override operator to print out the details of building tile
std::ostream& operator<<(std::ostream& os, BuildingTile& bt)
{
	std::string type = bt.typeToString();
	int value = bt.getValue();
	os << "Details of Building Tile:" << std::endl;
	os << "+ Type: " << type << std::endl;
	os << "+ Value: " << value << std::endl;

	return os;
}
