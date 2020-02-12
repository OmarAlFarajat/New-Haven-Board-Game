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
