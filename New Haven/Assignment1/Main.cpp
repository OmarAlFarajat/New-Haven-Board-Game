#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "GBMap.h"
#include "Resources.h"
#include "Harvest.h"
#include "Building.h"
#include "Hand.h"
#include "Player.h"
#include "GBMapLoader.h"
#include "TileNode.h"
#include "VGMap.h"
#include "VGMapLoader.h"


/* Global Variables for the game*/
static int numberOfPlayers;
static std::string mapFileName = "";
static GBMap* gb_map = new GBMap();
static VGMap* vg_map = new VGMap();
static HarvestDeck harvestDeck;
static BuildingDeck buildingDeck;

static std::vector<Player> players;
/*-------------------------------*/

void initialize() {
	std::cout << "Initialize global variables::" << std::endl;

	// User prompted for number of players
	std::cout << "Please enter the number of players: "; 
	std::cin >> numberOfPlayers; 
	std::cout << std::endl; 

	// Switch statement assigns a string to fileName
	switch(numberOfPlayers){
	case 2:
		//mapFileName = "GBA_2Players.gbmap";
		mapFileName = "GBA_2Players_resourceTest.gbmap";
		//mapFileName = "GBA_2Players_invalid.gbmap";
		break;
	case 3:
		mapFileName = "GBA_3Players.gbmap";
		break;
	case 4:
		mapFileName = "GBA_4Players.gbmap";
		break;
	default:
		std::cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << std::endl;
	}

	loadGBMap(mapFileName, *gb_map);
	// Display which map was loaded
	std::cout << "GB Map has been created from " << mapFileName << "." << std::endl;
	std::cout << std::endl; 

	for (int i = 0; i < numberOfPlayers; ++i) {
		players.push_back(Player());
	}
}

void testGBMap() {
	// Print a verbose and non-verbose grid-graph of the tile map and check if it's connected.
	std::cout << "Initial tile graph state. The format is id(up, right, down, left, visited, enabled). " << gb_map->getTileGraph()->getNumEnabledNodes() << " active nodes." << std::endl;
	std::cout << std::endl;
	gb_map->getTileGraph()->printGridGraph(false);
	gb_map->getTileGraph()->printGridGraph(true);
	std::cout << "Is connected? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getNode(0)) << std::endl;
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
	std::cout << "Is connected and valid? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getNode(23)) << std::endl;
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
}

void testVGMap() {
	std::string vgFileName = "Stratford_example.vgmap";

	loadVGMap(vgFileName, *vg_map);

	std::cout << "VG Map has been created from " << vgFileName << "." << std::endl;

	std::cout << std::endl;

	vg_map->getBuildingGraph()->printGridGraph(false);

	std::cout << "Is VGMap connected? " << std::boolalpha << vg_map->getBuildingGraph()->isConnected_DFS(vg_map->getBuildingGraph()->getNode(7)) << std::endl;
	std::cout << std::endl;

	vg_map->getBuildingGraph()->printGridGraph(true);
}

void testHarvestDeck() {
	std::cout << "Enter testing for Harvest" << std::endl;
	std::cout << "Creating a random HarvestTile" << std::endl;
	HarvestTile randomHT;
	std::cout << "Displaying that random HarvestTile" << std::endl;
	std::cout << randomHT<< std::endl;
	
	const int loopCtr = 6; // Change the number of time drawing a tile for testing
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Harvest tile from the Deck-- Displaying details of the tile: \n" << std::endl;
		HarvestTile* tile = harvestDeck.draw();

		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << harvestDeck.getNumOfRemain() << std::endl;
}

void testBuildingDeck() {
	std::cout << "Enter testing for Building Deck" << std::endl;

	const int loopCtr = 5; //Change the number of time drawing a tile 
	for (int i = 0; i < loopCtr; ++i) {
		std::cout << "Drawing a Building tile from the Deck \n" << std::endl;
		BuildingTile* tile = buildingDeck.draw();
		std::cout << *tile << std::endl;
		std::cout << std::endl;
	}

	std::cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << buildingDeck.getNumOfRemain() << std::endl;
}

void testHandObj() {
	std::cout << "Enter testing for Hand Object" << std::endl;
	Hand mine;
	std::cout << "Testing for ability to hold objects" << std::endl;
	int loop = 2;
	for (int i = 0; i < loop; ++i) {
		mine.addHarvestTile(harvestDeck.draw());
		mine.addBuildingTile(buildingDeck.draw());
	}
	std::cout << "Showing cards on Hand after drawing from the Deck" << std::endl;
	mine.showHand();

	std::cout << "Test a turn of playing Harvest Tile" << std::endl;
	mine.playHarvest(gb_map);
}

void testResourceCount() {
	std::map<ResourceType, int> resourcesCollected = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };

	// We use tile node 0 as an example. In the game, it will be the tile placed down by the player. 
	gb_map->calcResourceAdjacencies(static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0)), resourcesCollected);

	// Print out the resources collected
	std::cout << "SHEEP: " << resourcesCollected[ResourceType::SHEEP] << std::endl;
	std::cout << "STONE: " << resourcesCollected[ResourceType::STONE] << std::endl;
	std::cout << "TIMBER: " << resourcesCollected[ResourceType::TIMBER] << std::endl;
	std::cout << "WHEAT: " << resourcesCollected[ResourceType::WHEAT] << std::endl;

	HarvestTile* node7 = new HarvestTile(new ResourceType[4]{ ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::TIMBER, ResourceType::SHEEP });
	HarvestTile* node12 = new HarvestTile(new ResourceType[4]{ ResourceType::TIMBER, ResourceType::SHEEP, ResourceType::STONE, ResourceType::STONE });

	gb_map->placeHarvestTile(node7, static_cast<TileNode*>(gb_map->getTileGraph()->getNode(7)));
	gb_map->placeHarvestTile(node12, static_cast<TileNode*>(gb_map->getTileGraph()->getNode(12)));

	std::cout << "After adding resources to nodes 7 and 12, we test resources collected from TileNode 0." << std::endl; 
	std::cout << std::endl; 
	resourcesCollected[ResourceType::SHEEP] = 0;
	resourcesCollected[ResourceType::STONE] = 0;
	resourcesCollected[ResourceType::TIMBER] = 0;
	resourcesCollected[ResourceType::WHEAT] = 0;

	// We use tile node 0 as an example. In the game, it will be the tile placed down by the player. 
	gb_map->calcResourceAdjacencies(static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0)), resourcesCollected);

	// Print out the resources collected
	std::cout << "SHEEP: " << resourcesCollected[ResourceType::SHEEP] << std::endl;
	std::cout << "STONE: " << resourcesCollected[ResourceType::STONE] << std::endl;
	std::cout << "TIMBER: " << resourcesCollected[ResourceType::TIMBER] << std::endl;
	std::cout << "WHEAT: " << resourcesCollected[ResourceType::WHEAT] << std::endl;
}

void testPlayer() {
	std::cout << "Enter testing for Player Object" << std::endl;
	Player* test = &players[0];

	int drawHarvest = 2;
	std::cout << "Drawing " << drawHarvest << " Harvest Tiles" << std::endl;
	for (int i = 0; i < drawHarvest; ++i) {
		test->DrawHarvestTile(&harvestDeck);
	}

	int drawBuilding = 4;
	std::cout << "Drawing " << drawBuilding << " Building Tiles" << std::endl;
	for (int i = 0; i < drawBuilding; ++i) {
		test->DrawBuilding(&buildingDeck);
	}

	std::cout << "\n==============================" << std::endl;
	std::cout << " SHOWING HAND AFTER DRAWING " << std::endl;
	test->show();
	std::cout << "\n==============================" << std::endl;

	std::cout << "Placing a Harvest Tile on the game board" << std::endl;
	test->PlaceHarvestTile(gb_map);
	std::cout << "Placing a Building Tile on the Village board" << std::endl;
	test->PlaceBuildingTile(test->getVGMap());
	test->show();

	std::cout << "NUMBER OF POINTS IS: " << test->getVGMap()->calculatePoints() << std::endl;
}

void printAllGraphs() {
	gb_map->getTileGraph()->printGridGraph(true);
	gb_map->getResourceGraph()->printGridGraph(true);
	players[0].getVGMap()->getBuildingGraph()->printGridGraph(true);
}

int main() {
	/*
	Generate a randomize seed according to the current machine time
	-- Need to be placed at the beginning of main to avoid bias for rand()
	*/
	srand(time(nullptr));

	// Always leave uncommented. This initializes intended for most of the test functions below. 
	initialize();
	
	/*	Uncomment any of the test functions below as desired. 
	*	It may be best to only test one at a time for clarity.*/

	//testGBMap();
	//testHarvestDeck();
	//testBuildingDeck();
	//testHandObj();
	//testResourceCount(); 	
	//testVGMap();
	//testPlayer();
	//printAllGraphs();

	delete gb_map;
	delete vg_map;

	return 0;
}
