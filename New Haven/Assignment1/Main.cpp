#include "GBMap.h"
#include "Node.h"
#include <iostream>
#include "Resources.h"

const int MAX_MAP_LENGTH = 7;
const int MAX_RESOURCE_LENGTH = 14; 

int main() {
	GBMap* gb_map = new GBMap();
	gb_map->mapGraph->makeSquareGrid(MAX_MAP_LENGTH, NodeType::MAP);
	gb_map->tileGraph->makeSquareGrid(MAX_MAP_LENGTH, NodeType::TILE);
	gb_map->resourceGraph->makeSquareGrid(MAX_RESOURCE_LENGTH, NodeType::RESOURCE);
	
	std::cout << "BEFORE DFS:" << std::endl;
	gb_map->resourceGraph->printGrid(MAX_RESOURCE_LENGTH);

	std::cout << "Number of nodes: " << gb_map->resourceGraph->getNumberOfNodes() << std::endl;
	std::cout << "Connected? " << std::boolalpha << gb_map->resourceGraph->isConnected_DFS(gb_map->resourceGraph->getRootNode()) << std::endl << std::endl;

	std::cout << "AFTER DFS:" << std::endl;
	gb_map->resourceGraph->printGrid(14);




	Resource resources[4] = { Resource(ResourceType::STONE), Resource(ResourceType::SHEEP), Resource(ResourceType::TIMBER), Resource(ResourceType::WHEAT) };

	HarvestTile harvestTile(resources, TileStatus::IN_PLAY);
	//gb_map->mapGraph->addNode();
}
