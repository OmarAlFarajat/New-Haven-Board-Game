#include<algorithm>
#include <vector>
#include "Building.h"

BuildingTile::BuildingTile()
{
	//Not gonna be used
}

BuildingTile::BuildingTile(BuildingColor color, BuildingType buildingType, int value)
{
	this->color = new BuildingColor(color);
	this->type = new BuildingType(buildingType);
	this->value = new int(value);

}

BuildingTile::~BuildingTile()
{
}

BuildingType* BuildingTile::getBuildingType()
{
	return this->type;
}

std::string BuildingTile::typeToString()
{
	std::string output;
	switch (*(this->type)) {
	case BuildingType::FOREST:
		output = "FOREST";
		break;
	case BuildingType::MEADOW:
		output = "MEADOW";
		break;
	case BuildingType::QUARRY:
		output = "QUARRY";
		break;
	case BuildingType::WHEATFIELD:
		output = "WHEATFIELD";
		break;
	default:
		output = "INVALID";
	}
	return output;
}

std::string BuildingTile::colorToString()
{
	std::string output;
	switch (*(this->color)) {
	case BuildingColor::GREEN:
		output = "GREEN";
		break;
	case BuildingColor::GREY:
		output = "GREY";
		break;
	case BuildingColor::RED:
		output = "RED";
		break;
	case BuildingColor::YELLOW:
		output = "YELLOW";
		break;
	default:
		output = "INVALID";
	}
	return output;

}

BuildingDeck::BuildingDeck()
{ 
	std::vector<BuildingType> typeLib = {
		BuildingType::MEADOW,
		BuildingType::QUARRY,
		BuildingType::FOREST,
		BuildingType::WHEATFIELD
	};

	std::vector<BuildingColor> colorLib = {
		BuildingColor::GREEN,
		BuildingColor::GREY,
		BuildingColor::RED,
		BuildingColor::YELLOW
	};


	/*
	Create a pointer of iterator type for building type
	Loop one color in colorLib one at a time
	Assign a value in range 1 -> 6 for each tile
	There are 36 tiles of one color (6 rows)
	There are 4 colors
	=> 36 * 4 = 144 tiles in the deck
	*/
	std::vector<BuildingType>::iterator typeIT = typeLib.begin();
	for (std::vector<BuildingColor>::iterator colorIT = colorLib.begin(); colorIT != colorLib.end(); ++colorIT) {
		int row = 1;
		while (row <= 6) {
			for (int value = 1; value <= 6; ++value) {
				BuildingTile newTile(*colorIT, *typeIT, value);
				this->deck.push_back(newTile);
			}
			row++;
		}

		typeIT++; // Move the pointer of type iterator up when changing the color
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
	std::string color = bt.colorToString();
	std::string type = bt.typeToString();
	int value = bt.getValue();
	os << "Details of Building Tile:" << std::endl;
	os << "+ Color: " << color << std::endl;
	os << "+ Type: " << type << std::endl;
	os << "+ Value: " << *bt.value << std::endl;

	return os;
}
