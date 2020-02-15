#include <iostream>
#include <string>
#include "GBMap.h"
#include "Resources.h"
#include "GBMapLoader.h"
#include "TileNode.h"

int main() {
	
	// Assume for this example that it's a 3-player board
	int numberOfPlayers = 0; 
	std::cout << "Please enter the number of players: "; 
	std::cin >> numberOfPlayers; 

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
		std::cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << std::endl;
		return 666;		// Hail Satan

	}
	GBMap* gb_map = new GBMap();
	loadMap(fileName, *gb_map);

	std::cout << "Initial tile graph with " << gb_map->tileGraph->getNumEnabledNodes() << " active nodes." << std::endl; 
	gb_map->tileGraph->printGridGraph(true);

	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getRootNode()) << std::endl;
	std::cout << "After DFS: " << std::endl;
	gb_map->tileGraph->printGridGraph(true);
	std::cout << "Resetting all nodes to unvisited..." << std::endl;
	gb_map->tileGraph->resetAllVisited();

	std::cout << "Disabling nodes 6, 7, 11, 12..." << std::endl;
	gb_map->tileGraph->disableNode(6);
	gb_map->tileGraph->disableNode(7);
	gb_map->tileGraph->disableNode(11);
	gb_map->tileGraph->disableNode(12);

	std::cout << "After disabling the nodes, the number of active nodes is " << gb_map->tileGraph->getNumEnabledNodes() << std::endl;
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getNode(23)) << std::endl;


	gb_map->tileGraph->printGridGraph(true);
	gb_map->tileGraph->resetAllVisited();
	
	std::cout << "The following are the four Resource nodes (by ID) linked to TileNode 10:" << std::endl;
	for(int i = 0; i < 4; i++)
		std::cout << static_cast<TileNode*>(gb_map->tileGraph->getNode(10))->getResourceNodes()[i]->getID() << " ";


}
