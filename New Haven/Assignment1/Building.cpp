#include<algorithm>
#include "Building.h"

BuildingTile::BuildingTile()
{
	value = new int(0);
	type = new ResourceType(ResourceType::NONE);
	faceUp = new bool(true);
}

BuildingTile::BuildingTile(ResourceType type, int value) 
{
	this->value = new int(value);
	this->type = new ResourceType(type); 
	this->faceUp = new bool(true);
}

BuildingTile::~BuildingTile()
{
	/*
	delete type;
	type = nullptr;
    delete value;
	value = nullptr;
	delete faceUp;
	faceUp = nullptr;
	*/
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
	Construct a building deck:
	Loop through each ResourceType inside typeLib at a time
	There are 36 tiles of one resourceType
	There are 4 kind of Resource
	=> 36 * 4 = 144 tiles in the deck
	*/

	const int numOfaType = 36;
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
	
	//After constructing a deck, shuffle every element to make the drawing unpredictable.
	std::random_shuffle(deck.begin(), deck.end()); 
	tileIndex = new int(numOfTiles); 
}

BuildingDeck::~BuildingDeck()
{
	delete tileIndex;
	tileIndex = nullptr;
}

// Draw a tile out of the deck
BuildingTile* BuildingDeck::draw()
{
	//since the deck was shuffled at the beginning, simply draw the tile on top
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
