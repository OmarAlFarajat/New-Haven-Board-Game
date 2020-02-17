#include "Building.h"

BuildingTiles::BuildingTiles()
{
	//Not gonna be used
}

BuildingTiles::BuildingTiles(BuildingColor color, BuildingType buildingType, int value)
{
	// Create a building tile as requested attributes
	this->Color = &color;
	this->Type = &buildingType;
	this->Value = &value;
}

BuildingTiles::~BuildingTiles()
{
}

BuildingType* BuildingTiles::getBuildingType()
{
	return this->Type;
}

BuildingDeck::BuildingDeck()
{ 
	/*
		TODO: Create a deck of building with different suits
	*/
}

BuildingDeck::~BuildingDeck()
{
}

BuildingTiles* BuildingDeck::draw()
{
	if (*tileIndex >= 0) {
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];
	}
	else { //deck is empty
		return NULL;
	}

}


