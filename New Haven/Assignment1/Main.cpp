#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include "GBMap.h"
#include "Resources.h"
#include "Harvest.h"
#include "Building.h"
#include "GBMapLoader.h"
#include "TileNode.h"

/* Global Variables for the game*/
static int numberOfPlayers;
static std::string mapFileName = "";
static GBMap* gb_map = new GBMap();

static HarvestDeck harvestDeck;
static BuildingDeck buildingDeck;
/*-------------------------------*/

int initialize() {
	std::cout << "Initialize global variables::" << std::endl;

	// User prompted for number of players
	std::cout << "Please enter the number of players: "; 
	std::cin >> numberOfPlayers; 
	std::cout << std::endl; 

	// Switch statement assigns a string to fileName
	switch(numberOfPlayers){
	case 2:
		mapFileName = "GBA_2Players.gbmap";
		break;
	case 3:
		mapFileName = "GBA_3Players.gbmap";
		break;
	case 4:
		mapFileName = "GBA_4Players.gbmap";
		break;
	case 666:
		mapFileName = "GBA_2Players_invalid.gbmap";
		break;
	default:
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		return 666;
	}

	loadMap(mapFileName, *gb_map);
	// Display which map was loaded
	std::cout << "Map has been created from " << mapFileName << "." << std::endl;
	std::cout << std::endl; 

	return 0;
}

int testGBMap() {
	// Print a verbose and non-verbose grid-graph of the tile map and check if it's connected.
	std::cout << "Initial tile graph state. The format is id(up, right, down, left, visited, enabled). " << gb_map->getTileGraph()->getNumEnabledNodes() << " active nodes." << std::endl;
	std::cout << std::endl;
	gb_map->getTileGraph()->printGridGraph(false);
	gb_map->getTileGraph()->printGridGraph(true);
	std::cout << "Is connected? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getRootNode()) << std::endl;
	std::cout << std::endl;
	
	// Disable nodes 1 and 5. In a 2-player or 3-player game, this will make node 0 disconnected from the rest of the nodes.
	std::cout << "Disabling nodes 1 and 5..." << std::endl;
	std::cout << std::endl;
	gb_map->getTileGraph()->disableNode(1);
	gb_map->getTileGraph()->disableNode(5);

	std::cout << "After disabling the nodes, the number of active nodes is " << gb_map->getTileGraph()->getNumEnabledNodes() << "..." << std::endl;
	std::cout << std::endl;
	std::cout << "After disabling nodes: " << std::endl;
	gb_map->getTileGraph()->printGridGraph(true);

	// After disabling the above nodes, the graph will not be connected and this output will show false.
	// Print the graph to show how the graph has become disconnected (missing edges)
	std::cout << "Is connected? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getNode(23)) << std::endl;
	std::cout << std::endl;
	// This demonstrates how a tile node can be linked to its four Resource nodes in the resource graph.
	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 0:" << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout << str << " | ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 5:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(5))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(5))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout <<  str << " | ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 8:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(8))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(8))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout << str << " | ";
	}
	std::cout << std::endl;

	return 0;
}

int testHarvestDeck() {
	std::cout << "Enter testing for Harvest" << std::endl;
	std::cout << "Creating a random HarvestTile" << std::endl;
	HarvestTile randomHT;
	std::cout << "Displaying that random HarvestTile" << std::endl;
	std::cout << randomHT<< std::endl;

	const int loopCtr = 5; // Change the number of time drawing a tile for testing
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Harvest tile from the Deck-- Displaying details of the tile: \n" << std::endl;
		HarvestTile* tile = harvestDeck.draw();
		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << harvestDeck.getNumOfRemain() << std::endl;

	return 0;
}

int testBuildingDeck() {
	std::cout << "Enter testing for Building Deck" << std::endl;

	const int loopCtr = 5; //Change the number of time drawing a tile 
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Building tile from the Deck \n" << std::endl;
		BuildingTile* tile = buildingDeck.draw();
		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << buildingDeck.getNumOfRemain() << std::endl;

	return 0;
}


int main() {
	/*
	Generate a randomize seed according to the current machine time
	-- Need to be placed at the beginning of main to avoid bias for rand()
	*/
	srand(static_cast<unsigned int>(time(nullptr)));

	//Initialize global variables
	if (initialize() != 0) {
		return 1;
	}
	
	/*
	Enable boolean values to display/debug parts
	--> Always set the boolean values to false before commiting
	*/

	// Enable Test for Gameboard map
	bool testGameboard= true;
	if (testGameboard) {
		testGBMap();
		std::cout << "<----------------->" << std::endl;
	}

	// Enable Test for Harvest
	bool testHarvest= true;
	if (testHarvest) {
		testHarvestDeck();
		std::cout << "<----------------->" << std::endl;
	}

	// Enable Test for Building
	bool testBuilding = true;
	if (testBuilding) {
		testBuildingDeck();
		std::cout << "<----------------->" << std::endl;
	}
	//-----------------------------------------

	std::cout << "--Done Testing--" << std::endl;
	return 0;
	}
