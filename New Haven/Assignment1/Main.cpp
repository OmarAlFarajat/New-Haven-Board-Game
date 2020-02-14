#include <iostream>
#include <string>
#include "GBMap.h"
#include "Resources.h"
#include "GBMapLoader.h"
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

	gb_map->tileGraph->printGridGraph(true);
	//gb_map->resourceGraph->printGridGraph(false);
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getRootNode()) << std::endl;
	gb_map->tileGraph->printGridGraph(true);

	// Disable nodes 1, 2, 6, 7
	gb_map->tileGraph->disableNode(1);
	gb_map->tileGraph->disableNode(5);
	gb_map->tileGraph->disableNode(6);
	//gb_map->tileGraph->disableNode(7);

	gb_map->tileGraph->resetAllVisited();
	std::cout << "Is connected? " << std::boolalpha << gb_map->tileGraph->isConnected_DFS(gb_map->tileGraph->getNode(23)) << std::endl;
	gb_map->tileGraph->printGridGraph(true);
	gb_map->tileGraph->resetAllVisited();
	gb_map->tileGraph->printGridGraph(true);



}
