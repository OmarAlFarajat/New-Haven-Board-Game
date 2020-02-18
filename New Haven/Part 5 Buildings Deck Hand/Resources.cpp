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

HarvestTiles::HarvestTiles()
{
}

HarvestTiles::~HarvestTiles()
{
}

bool HarvestTiles::isContain(ResourceType type)
{
	return false;
}

HarvestDeck::HarvestDeck()
{
}

HarvestDeck::~HarvestDeck()
{
}

HarvestTiles HarvestDeck::draw()
{
	return HarvestTiles();
}

BuildingTile::BuildingTile()
{
}

BuildingTile::BuildingTile(BuildingColor color, BuildingType buildingType, int value)
{
}

BuildingTile::~BuildingTile()
{
}

BuildingType BuildingTile::getBuildingType()
{
	return BuildingType();
}

BuildingDeck::BuildingDeck()
{
}

BuildingDeck::~BuildingDeck()
{
}

BuildingTile BuildingDeck::draw()
{
	return BuildingTile();
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
