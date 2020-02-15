#include "Harvest.h"
#include "Resources.h"

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

