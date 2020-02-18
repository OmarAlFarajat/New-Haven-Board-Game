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

int testHarvestDeck() {
	std::cout << "Enter testing for Harvest" << std::endl;
	std::cout << "Creating a random HarvestTile" << std::endl;
	HarvestTile randomHT;
	std::cout << "Displaying that random HarvestTile" << std::endl;
	std::cout << randomHT<< std::endl;

	std::cout << "Creating a Harvest Deck" << std::endl;
	HarvestDeck deck;

	const int loopCtr = 5; // Change the number of time drawing a tile for testing
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Harvest tile -- Displaying details of the tile: \n" << std::endl;
		HarvestTile* tile = deck.draw();
		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << deck.getNumOfRemain() << std::endl;

	return 0;
}

int testBuildingDeck() {
	std::cout << "Enter testing for Building Deck" << std::endl;
	std::cout << "Creating a Building Deck" << std::endl;
	BuildingDeck deck;

	const int loopCtr = 5; //Change the number of time drawing a tile 
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Building tile \n" << std::endl;
		BuildingTile* tile = deck.draw();
		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << deck.getNumOfRemain() << std::endl;

	return 0;
}

int main() {
	/*
	Generate a random seed according to the current machine time
	-- Need to be placed at the beginning of main to avoid bias for rand()
	*/
	srand(time(NULL)); 
	
	/*
	Enable boolean values to display/debug parts
	--> Always set the boolean values to false before commiting
	*/
	//----------------------------------------
	// Enable Test for Harvest
	bool testHarvest= false;
	if (testHarvest) {
		testHarvestDeck();
		return 0;
	}
	//-----------------------------------------
	// Enable Test for Building
	bool testBuilding = false;
	if (testBuilding) {
		testBuildingDeck();
		return 0;
	}
	//-----------------------------------------

	// User prompted for number of players
	int numberOfPlayers = 0; 
	std::cout << "Please enter the number of players: "; 
	std::cin >> numberOfPlayers; 
	std::cout << std::endl; 

	// Switch statement assigns a string to fileName
	std::string fileName = ""; 
	switch(numberOfPlayers){
	case 2:
		fileName = "GBA_2Players.gbmap";
		break;
	case 3:
		fileName = "GBA_3Players.gbmap";
		break;
	case 4:
		fileName = "GBA_4Players.gbmap";
		break;
	case 666:
		fileName = "GBA_2Players_invalid.gbmap";
		break;
	default:
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		return 666;
	}
	// Create an instance of GBMap class and pass it and the file name to loadMap()
	GBMap* gb_map = new GBMap();
	loadMap(fileName, *gb_map);

	// Display which map was loaded
	std::cout << "Map has been created from " << fileName << "." << std::endl;
	std::cout << std::endl; 

	// Print a verbose and non-verbose grid-graph of the tile map and check if it's connected.
	std::cout << "Initial tile graph state. The format is id(up, right, down, left, visited, enabled). " << gb_map->tileGraph->getNumEnabledNodes() << " active nodes." << std::endl; 
	std::cout << std::endl;
	gb_map->tileGraph->printGridGraph(false);
	gb_map->tileGraph->printGridGraph(true);
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getRootNode()) << std::endl;
	std::cout << std::endl;
	
	// Disable nodes 1 and 5. In a 2-player or 3-player game, this will make node 0 disconnected from the rest of the nodes.
	std::cout << "Disabling nodes 1 and 5..." << std::endl;
	std::cout << std::endl;
	gb_map->tileGraph->disableNode(1);
	gb_map->tileGraph->disableNode(5);

	std::cout << "After disabling the nodes, the number of active nodes is " << gb_map->tileGraph->getNumEnabledNodes() << "..." << std::endl;
	std::cout << std::endl;
	std::cout << "After disabling nodes: " << std::endl;
	gb_map->tileGraph->printGridGraph(true);

	// After disabling the above nodes, the graph will not be connected and this output will show false.
	// Print the graph to show how the graph has become disconnected (missing edges)
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getNode(23)) << std::endl;
	std::cout << std::endl;
	// This demonstrates how a tile node can be linked to its four Resource nodes in the resource graph.
	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 0:" << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->tileGraph->getNode(0))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->tileGraph->getNode(0))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout << str << " | ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 5:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->tileGraph->getNode(5))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->tileGraph->getNode(5))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout <<  str << " | ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 8:" << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->tileGraph->getNode(8))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string str = static_cast<TileNode*>(gb_map->tileGraph->getNode(8))->getResourceNodes()[i]->getTypeAsString().c_str();
		std::cout << str << " | ";
	}
	std::cout << std::endl;
}


