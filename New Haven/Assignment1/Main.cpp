#include "GBMap.h"
#include "Node.h"
#include <iostream>
#include "Resources.h"

int main() {
	GBMap* gb_map = new GBMap();
	gb_map->makeSquareGrid(7);

	std::cout << "BEFORE DFS:" << std::endl;
	gb_map->printGrid(7);

	std::cout << "Number of nodes: " << gb_map->getNumberOfNodes() << std::endl;
	std::cout << "Connected? " << std::boolalpha << gb_map->isConnected_DFS(gb_map->getRootNode()) << std::endl << std::endl;

	std::cout << "AFTER DFS:" << std::endl;
	gb_map->printGrid(7);

	Resource temp(ResourceType::STONE);

}
