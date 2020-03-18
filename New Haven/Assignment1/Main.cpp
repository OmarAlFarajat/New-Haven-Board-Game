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

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


/* Global Variables for the game*/
static int numberOfPlayers;
static string mapFileName = "";
static GBMap* gb_map = new GBMap();
static VGMap* vg_map = new VGMap();
static HarvestDeck harvestDeck;
static BuildingDeck buildingDeck;

static vector<Player> players;
/*-------------------------------*/

void initialize() {
	cout << "Initialize global variables::" << endl;

	// User prompted for number of players
	cout << "Please enter the number of players: "; 
	cin >> numberOfPlayers; 
	cout << endl; 

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
		cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << endl;
	}

	loadGBMap(mapFileName, *gb_map);
	// Display which map was loaded
	cout << "GB Map has been created from " << mapFileName << "." << endl;
	cout << endl; 

	for (int i = 0; i < numberOfPlayers; ++i) {
		players.push_back(Player());
	}
}

void testGBMap() {
	// Print a verbose and non-verbose grid-graph of the tile map and check if it's connected.
	cout << "Initial tile graph state. The format is id(up, right, down, left, visited, enabled). " << gb_map->getTileGraph()->getNumEnabledNodes() << " active nodes." << endl;
	cout << endl;
	gb_map->getTileGraph()->printGridGraph(false);
	gb_map->getTileGraph()->printGridGraph(true);
	cout << "Is connected? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getNode(0)) << endl;
	cout << endl;
	
	// Disable nodes 1 and 5. In a 2-player or 3-player game, this will make node 0 disconnected from the rest of the nodes.
	cout << "Disabling nodes 1 and 5..." << endl;
	cout << endl;
	gb_map->getTileGraph()->disableNode(1);
	gb_map->getTileGraph()->disableNode(5);

	cout << "After disabling the nodes, the number of active nodes is " << gb_map->getTileGraph()->getNumEnabledNodes() << "..." << endl;
	cout << endl;
	cout << "After disabling nodes: " << endl;
	gb_map->getTileGraph()->printGridGraph(true);

	// After disabling the above nodes, the graph will not be connected and this output will show false.
	// Print the graph to show how the graph has become disconnected (missing edges)
	cout << "Is connected and valid? " << std::boolalpha << gb_map->getTileGraph()->isConnected_DFS(gb_map->getTileGraph()->getNode(23)) << endl;
	cout << endl;
	// This demonstrates how a tile node can be linked to its four Resource nodes in the resource graph.
	cout << "The following are the four Resource nodes (by ID) linked to TileNode 0:" << endl;
	for(int i = 0; i < 4; i++)
		cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0))->getResourceNodes()[i]->getID() << " ";
	cout << endl;
	for (int i = 0; i < 4; i++) {
		string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0))->getResourceNodes()[i]->getTypeAsString().c_str();
		cout << str << " | ";
	}
	cout << endl;
	cout << endl;

	cout << "The following are the four Resource nodes (by ID) linked to TileNode 5:" << endl;
	for (int i = 0; i < 4; i++)
		cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(5))->getResourceNodes()[i]->getID() << " ";
	cout << endl;
	for (int i = 0; i < 4; i++) {
		string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(5))->getResourceNodes()[i]->getTypeAsString().c_str();
		cout <<  str << " | ";
	}
	cout << endl;
	cout << endl;

	cout << "The following are the four Resource nodes (by ID) linked to TileNode 8:" << endl;
	for (int i = 0; i < 4; i++)
		cout << static_cast<TileNode*>(gb_map->getTileGraph()->getNode(8))->getResourceNodes()[i]->getID() << " ";
	cout << endl;
	for (int i = 0; i < 4; i++) {
		string str = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(8))->getResourceNodes()[i]->getTypeAsString().c_str();
		cout << str << " | ";
	}
	cout << endl;
}

void testVGMap() {
	string vgFileName = "Stratford_example.vgmap";

	loadVGMap(vgFileName, *vg_map);

	cout << "VG Map has been created from " << vgFileName << "." << endl;

	cout << endl;

	vg_map->getBuildingGraph()->printGridGraph(false);

	cout << "Is VGMap connected? " << std::boolalpha << vg_map->getBuildingGraph()->isConnected_DFS(vg_map->getBuildingGraph()->getNode(7)) << endl;
	cout << endl;

	vg_map->getBuildingGraph()->printGridGraph(true);
}

void testHarvestDeck() {
	cout << "Enter testing for Harvest" << endl;
	cout << "Creating a random HarvestTile" << endl;
	HarvestTile randomHT;
	cout << "Displaying that random HarvestTile" << endl;
	cout << randomHT<< endl;
	
	const int loopCtr = 6; // Change the number of time drawing a tile for testing
	for (int i = 0; i < loopCtr; ++i) {
		cout << "Drawing a Harvest tile from the Deck-- Displaying details of the tile: \n" << endl;
		HarvestTile* tile = harvestDeck.draw();

		cout << *tile << endl;
		cout << endl;
	}

	cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << harvestDeck.getNumOfRemain() << endl;
}

void testBuildingDeck() {
	cout << "Enter testing for Building Deck" << endl;

	const int loopCtr = 5; //Change the number of time drawing a tile 
	for (int i = 0; i < loopCtr; ++i) {
		cout << "Drawing a Building tile from the Deck \n" << endl;
		BuildingTile* tile = buildingDeck.draw();
		cout << *tile << endl;
		cout << endl;
	}

	cout << "NUMBER OF REMAINNING CARD IN THE DECK: " << buildingDeck.getNumOfRemain() << endl;
}

void testHandObj() {
	cout << "Enter testing for Hand Object" << endl;
	Hand mine;
	cout << "Testing for ability to hold objects" << endl;
	int loop = 2;
	for (int i = 0; i < loop; ++i) {
		mine.addHarvestTile(harvestDeck.draw());
		mine.addBuildingTile(buildingDeck.draw());
	}
	cout << "Showing cards on Hand after drawing from the Deck" << endl;
	mine.showHand();

	cout << "Test a turn of playing Harvest Tile" << endl;
	mine.playHarvest(gb_map);
}

void testResourceCount() {
	std::map<ResourceType, int> resourcesCollected = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };

	// We use tile node 0 as an example. In the game, it will be the tile placed down by the player. 
	gb_map->calcResourceAdjacencies(static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0)), resourcesCollected);

	// Print out the resources collected
	cout << "SHEEP: " << resourcesCollected[ResourceType::SHEEP] << endl;
	cout << "STONE: " << resourcesCollected[ResourceType::STONE] << endl;
	cout << "TIMBER: " << resourcesCollected[ResourceType::TIMBER] << endl;
	cout << "WHEAT: " << resourcesCollected[ResourceType::WHEAT] << endl;

	HarvestTile* node7 = new HarvestTile(new ResourceType[4]{ ResourceType::SHEEP, ResourceType::SHEEP, ResourceType::TIMBER, ResourceType::SHEEP });
	HarvestTile* node12 = new HarvestTile(new ResourceType[4]{ ResourceType::TIMBER, ResourceType::SHEEP, ResourceType::STONE, ResourceType::STONE });

	gb_map->placeHarvestTile(node7, static_cast<TileNode*>(gb_map->getTileGraph()->getNode(7)));
	gb_map->placeHarvestTile(node12, static_cast<TileNode*>(gb_map->getTileGraph()->getNode(12)));

	cout << "After adding resources to nodes 7 and 12, we test resources collected from TileNode 0." << endl; 
	cout << endl; 
	resourcesCollected[ResourceType::SHEEP] = 0;
	resourcesCollected[ResourceType::STONE] = 0;
	resourcesCollected[ResourceType::TIMBER] = 0;
	resourcesCollected[ResourceType::WHEAT] = 0;

	// We use tile node 0 as an example. In the game, it will be the tile placed down by the player. 
	gb_map->calcResourceAdjacencies(static_cast<TileNode*>(gb_map->getTileGraph()->getNode(0)), resourcesCollected);

	// Print out the resources collected
	cout << "SHEEP: " << resourcesCollected[ResourceType::SHEEP] << endl;
	cout << "STONE: " << resourcesCollected[ResourceType::STONE] << endl;
	cout << "TIMBER: " << resourcesCollected[ResourceType::TIMBER] << endl;
	cout << "WHEAT: " << resourcesCollected[ResourceType::WHEAT] << endl;

	delete node7;
	node7 = nullptr;
	delete node12;
	node12 = nullptr;

}

void testPlayer() {
	cout << "Enter testing for Player Object" << endl;
	Player* test = &players[0];

	int drawHarvest = 2;
	cout << "Drawing " << drawHarvest << " Harvest Tiles" << endl;
	for (int i = 0; i < drawHarvest; ++i) {
		test->DrawHarvestTile(&harvestDeck);
	}

	int drawBuilding = 4;
	cout << "Drawing " << drawBuilding << " Building Tiles" << endl;
	for (int i = 0; i < drawBuilding; ++i) {
		test->DrawBuilding(&buildingDeck);
	}

	cout << "\n==============================" << endl;
	cout << " SHOWING HAND AFTER DRAWING " << endl;
	test->show();
	cout << "\n==============================" << endl;

	cout << "Placing a Harvest Tile on the game board" << endl;
	test->PlaceHarvestTile(gb_map);
	cout << "Placing a Building Tile on the Village board" << endl;
	test->PlaceBuildingTile(test->getVGMap());
	test->show();

	cout << "NUMBER OF POINTS IS: " << test->getVGMap()->calculatePoints() << endl;
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
	gb_map = nullptr;
	delete vg_map;
	vg_map = nullptr;

	return 0;
}
