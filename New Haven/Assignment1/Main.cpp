#include <iostream>
#include <string>
#include "GBMap.h"
#include "Resources.h"
#include "GBMapLoader.h"
#include "TileNode.h"

int main() {
	// User prompted for number of players
	int numberOfPlayers = 0; 
	std::cout << "Please enter the number of players: "; 
	std::cin >> numberOfPlayers; 

	// Switch statement assigns a string to fileName
	std::string fileName = ""; 
	switch(numberOfPlayers){
	case 2:
		fileName = "GB_A_2_Players.gbmap";
		break;
	case 3:
		fileName = "GB_A_3_Players.gbmap";
		break;
	case 4:
		fileName = "GB_A_4_Players.gbmap";
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

	// Print a verbose grid graph of the tile map and check if it's connected.
	std::cout << "Initial tile graph state. The format is id(up, right, down, left, visited, enabled). " << gb_map->tileGraph->getNumEnabledNodes() << " active nodes." << std::endl; 
	std::cout << std::endl;
	gb_map->tileGraph->printGridGraph(true);
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getRootNode()) << std::endl;
	std::cout << std::endl;

	// Print the resulting graph to show that all nodes have been visited, then reset all nodes to unvisited. 
	std::cout << "After DFS: " << std::endl;
	gb_map->tileGraph->printGridGraph(true);
	std::cout << std::endl;
	
TODO: /* Currently, resetAllVisited() must be called each time after isConnected_DFS() 
	  in order to reset the graph to the default state. Ideally, this should be done at 
	  the last recursive resolution of isConnected_DFS(). */

	std::cout << "Resetting all nodes to unvisited..." << std::endl;
	gb_map->tileGraph->resetAllVisited();
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
	std::cout << "After DFS: " << std::endl;
	gb_map->tileGraph->printGridGraph(true);

	// Resetting all the nodes 
	std::cout << "Resetting all nodes to unvisited..." << std::endl;
	gb_map->tileGraph->resetAllVisited();
	std::cout << std::endl;

	// This demonstrates how a tile node can be linked to its four Resource nodes in the resource graph.
	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 10:" << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->tileGraph->getNode(10))->getResourceNodes()[i]->getID() << " ";
	std::cout << std::endl;

}
