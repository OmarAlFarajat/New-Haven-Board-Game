#include <vector>
#include <stdlib.h> 
#include <time.h>
#include "Harvest.h"
#include "Resources.h"

HarvestTile::HarvestTile()
{
	std::vector<ResourceType> temp;
	
	/*
	A for loop to iterate over the enum class of ResourceType
	With each resource type, create 3 instance and push to a temporary vector
	*/
	for (std::vector<ResourceType>::const_iterator it = temp.begin()++; it != temp.end(); ++it) {
		for (int i = 0; i < 3; ++i) {
			temp.push_back(*it);
		}
	}

	/*
	+ Pick a random index with seed of the current time 
	+ Create a new Resource with the ResourceType of the picked index
	+ Push the new Resource into the container of the Tile.
	+ Erase the picked resource out of temp
	+ => Perform 4 times to get 4 resources for a tile
	*/
	for (int i = 0; i < numOfResource; ++i) {
		srand(time(NULL));
		int randNum = (rand() % temp.size())+ 0;

		Resource newResource;
		newResource.setType(temp[randNum]);
		this->container.push_back(newResource);
		temp.erase(temp.begin() + randNum);

	}

}

HarvestTile::HarvestTile(Resource resources[4])
{
	for (int i = 0; i < 4; ++i) {
		container.push_back(resources[i]);
	}
}

HarvestTile::~HarvestTile()
{
}

HarvestDeck::HarvestDeck()
{
	/*
	A for-loop initializes a deck containning 60 harvest tiles
	*/
	for (int i = 0; i < this->numOfTiles; ++i) {
		this->deck.push_back(HarvestTile());
	}
	tileIndex = new int(numOfTiles);
}

HarvestDeck::~HarvestDeck()
{
}

HarvestTile* HarvestDeck::draw()
{
	if (*tileIndex > 0) { 
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];

	}
	else { //Deck is empty
		return NULL;

	}
}

