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

		Resource newResource;
		newResource.setType(typeLib[randNum]);

		this->container.push_back(newResource);
		typeLib.erase(typeLib.begin() + randNum);

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

//Override << operator to print out details of a Harvest Tile for debugging purpose
std::ostream& operator<<(std::ostream& os, HarvestTile& ht) 
{
	/*
		TODO: Figure out how to deal with NULL pointer when trying to display 
		a NULL card <trying to draw when deck is empty>
	*/
	std::vector<std::string> output;
	// Loop through the container and get the type of Resource in each position
	for (std::vector<Resource>::iterator it = ht.container.begin(); it!= ht.container.end(); ++it) {
		Resource temp = *it;
		std::string target = temp.getTypeAsString();
		if (target.compare("TIMBER") == 0) {
			output.push_back("TIMBER");
		}
		else if (target.compare("STONE") == 0 ) {
			output.push_back("STONE");
		}
		else if (target.compare("WHEAT") == 0) {
			output.push_back("WHEAT");
		} 
		else if (target.compare("SHEEP") == 0) {
			output.push_back("SHEEP");
		}
		else {
			output.push_back("INVALID RESOURCE -->>> NEED DEBUG");
		}
	}

	// Print out to the screen
	/* 
	Format:
	||STONE||SHEEP
	||WHEAT||TIMBER
	*/
	const std::string separator = " || ";
	int counter = 0;
	for (std::vector<std::string>::iterator it = output.begin(); it!=output.end(); ++it) {
		os << *it << separator;
		counter++;
		if (counter >= 2) {
			os << std::endl;
			counter = 0;
		}
	}
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

