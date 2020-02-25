#include <vector>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include "Resources.h"
#include "Harvest.h"

HarvestTile::HarvestTile()
{
	std::vector<ResourceType> typeLib;
	std::vector<ResourceType> resourceList= {
		ResourceType::TIMBER,
		ResourceType::STONE,
		ResourceType::WHEAT,
		ResourceType::SHEEP
	};
	
	/* FUNCTION TO INIT THE ALLOWED LIST OF TYPE
	A for loop to iterate over the vector containning the allowed types
	With each resource type, create 3 instances and push to a temporary vector -- typeLib
	*/
	for (std::vector<ResourceType>::iterator it = resourceList.begin(); it != resourceList.end(); ++it) {
		for (int i = 0; i < 3; ++i) {
			typeLib.push_back(*it);
		}
	}

	/*
	+ Create a new Resource with the ResourceType of the picked index
	+ Push the new Resource into the container of the Tile.
	+ Erase the picked resource out of typeLib
	=> Perform 4 times to get 4 resources for a tile
	*/
	for (int i = 0; i < numOfResource; ++i) {
		int randNum = (rand() % typeLib.size())+ 0;

		ResourceType newResource;
		newResource = typeLib[randNum];

		this->container.push_back(newResource);
		typeLib.erase(typeLib.begin() + randNum);

	}

}

HarvestTile::HarvestTile(ResourceType resources[4])
{
	for (int i = 0; i < 4; ++i) {
		container.push_back(resources[i]);
	}
}

HarvestTile::~HarvestTile()
{
}

//Override << operator to print out details of a Harvest Tile for debugging purpose
std::ostream& operator<<(std::ostream& os, HarvestTile& ht) 
{
	/*
		TODO: Figure out how to deal with NULL pointer when trying to display 
		a NULL card <trying to draw when deck is empty>
	*/
	std::vector<std::string> output;
	// Loop through the container and get the type of Resource in each position
	for (std::vector<ResourceType>::iterator it = ht.container.begin(); it!= ht.container.end(); ++it) {
		switch (*it) {
		case ResourceType::SHEEP:
			output.push_back("SHEEP");
			break;
		case ResourceType::STONE:
			output.push_back("STONE");
			break;
		case ResourceType::TIMBER:
			output.push_back("TIMBER");
			break;
		case ResourceType::WHEAT:
			output.push_back("WHEAT");
			break;
		default:
			output.push_back("INVALID RESOURCE -->>> NEED DEBUG");
		}

}

	// Print out to the screen
	/* 
	Format:
	|| STONE || SHEEP ||
	|| WHEAT || TIMBER ||
	*/
	
	std::string separator = " || ";
	os << separator << output[0] << separator << output[1] << separator << std::endl;
	os << separator << output[3] << separator << output[2] << separator << std::endl;
	return os;
}

HarvestDeck::HarvestDeck()
{
	//A for-loop initializes a deck containning 60 harvest tiles
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
	if (*tileIndex >= 0) { 
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];
	}
	else { //Deck is empty
		return NULL;
	}
}

int HarvestDeck::getNumOfRemain() const
{
	return *this->tileIndex;
}

