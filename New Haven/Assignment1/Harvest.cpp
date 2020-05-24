#include <string>
#include <cstdlib>
#include <ctime>
#include "Harvest.h"

using std::endl;
using std::string;

HarvestTile::HarvestTile()
{
	vector<ResourceType> typeLib;
	vector<ResourceType> resourceList= {
		ResourceType::TIMBER,
		ResourceType::STONE,
		ResourceType::WHEAT,
		ResourceType::SHEEP
	};
	
	/* FUNCTION TO INIT THE ALLOWED LIST OF TYPE
	A for loop to iterate over the vector containning the allowed types
	With each resource type, create 3 instances and push to a temporary vector -- typeLib
	*/
	for (vector<ResourceType>::iterator it = resourceList.begin(); it != resourceList.end(); ++it) {
		for (int i = 0; i < 3; ++i) {
			typeLib.push_back(*it);
		}
	}

	/*
	+ Create a new Resource with the ResourceType of the picked index
	+ Push the new Resource into the container of the Tile.
	+ Erase the picked resource out of typeLib
	=> Perform 4 times to get 4 resources for a tile 
	=> Avoid having a Harvest Tile with 4 of the same resources.
	*/
	for (int i = 0; i < numOfResource; ++i) {
		int randNum = (rand() % typeLib.size())+ 0;

		ResourceType newResource;
		newResource = typeLib[randNum];

		this->container.push_back(newResource);
		typeLib.erase(typeLib.begin() + randNum);

	}

	shipmentTile = new bool(false);
	shipmentContainer = new vector<ResourceType*>();
	isSelected = new bool(false);
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
ostream& operator<<(ostream& os, HarvestTile& ht) 
{
	vector<string> output;

	if (ht.isShipmentTile()) {
		os << ("SHIPMENT TILE: RESOURCES ARE LOCKED") << endl;
		for (int i = 0; i < 4; ++i) {
			output.push_back(" ? ");
		}
	}
	else {
		// Loop through the container and get the type of Resource in each position
		for (vector<ResourceType>::iterator it = ht.container.begin(); it!= ht.container.end(); ++it) {
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
	}

	// Print out to the screen
	/* 
	Format:
	|| STONE || SHEEP ||
	|| WHEAT || TIMBER ||
	*/
	
	string separator = " || ";
	os << separator << output[0] << separator << output[1] << separator << endl;
	os << separator << output[3] << separator << output[2] << separator << endl;
	return os;
}

bool HarvestTile::makeShipmentOf(ResourceType type) {
	if (isShipmentTile()) {
		for (int i = 0; i < numOfResource; ++i) {
			shipmentContainer->push_back(new ResourceType(type));
		}
		return true;
	}
	else {
		return false; // Wrong call, the tile is not a shipment
	}
}

HarvestDeck::HarvestDeck()
{
    srand((int) time(nullptr));
	//A for-loop initializes a deck containning 60 harvest tiles
	for (int i = 0; i < this->numOfTiles; ++i) {
		this->deck.push_back(HarvestTile());
	}
	tileIndex = new int(numOfTiles);
}

HarvestDeck::~HarvestDeck()
{
	delete tileIndex;
	tileIndex = nullptr;
}

HarvestTile* HarvestDeck::draw()
{
	if (*tileIndex >= 0) { 
		*tileIndex = *tileIndex - 1;
		return &deck[*tileIndex];
	}
	else { //Deck is empty
		return nullptr;
	}
}

