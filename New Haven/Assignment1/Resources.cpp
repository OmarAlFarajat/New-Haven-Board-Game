#include "Resources.h"

Resource::Resource()
{
}

Resource::Resource(ResourceType type)
{
}

Resource::~Resource()
{
}

HarvestTile::HarvestTile()
{
}

HarvestTile::HarvestTile(Resource resources[4], TileStatus status)
{
	*this->resources = resources;
	this->status = &status;
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
