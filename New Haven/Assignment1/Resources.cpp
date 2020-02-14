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

HarvestTile::HarvestTile()
{
}

HarvestTile::HarvestTile(Resource resources[4])
{
	*this->resources = resources;
}

HarvestTile::~HarvestTile()
{
}

HarvestDeck::HarvestDeck()
{
}

HarvestDeck::~HarvestDeck()
{
}

HarvestTile HarvestDeck::draw()
{
	return HarvestTile();
}

BuildingTiles::BuildingTiles()
{
}

BuildingTiles::BuildingTiles(BuildingColor color, BuildingType buildingType, int value)
{
}

BuildingTiles::~BuildingTiles()
{
}

BuildingType BuildingTiles::getBuildingType()
{
	return BuildingType();
}

BuildingDeck::BuildingDeck()
{
}

BuildingDeck::~BuildingDeck()
{
}

BuildingTiles BuildingDeck::draw()
{
	return BuildingTiles();
}

hand::hand()
{
}

hand::~hand()
{
}

void hand::exchange()
{
}
