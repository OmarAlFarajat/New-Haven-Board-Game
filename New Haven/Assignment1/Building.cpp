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


}

BuildingDeck::~BuildingDeck()
{
}

BuildingTiles* BuildingDeck::draw()
{
}


