#include "Hand.h"

Hand::Hand()
{
	numOfHarvest = new int(0);
	numOfBuilding = new int(0);
	harvestHold = new std::vector<HarvestTile*>(0);
	buildingHold = new std::vector<BuildingTile*>(0);

}

Hand::~Hand()
{
}

void Hand::showHand()
{
	std::cout << "Showing cards on hand:" << std::endl;
	for (int i = 0; i < this->getRemainHarvest(); ++i) {
		std::cout << "Harvest Tile no." << i << std::endl;
		std::cout << *harvestHold[0][i] << std::endl;
	}
	for (int i = 0; i < this->getRemainBuilding(); ++i) {
		std::cout << "Building Tile no." << i << std::endl;
		std::cout << *buildingHold[0][i] << std::endl;
	}

}

void Hand::addHarvestTile(HarvestTile* ht)
{
	harvestHold->push_back(ht);
	*numOfHarvest = *numOfHarvest + 1;
}

void Hand::addBuildingTile(BuildingTile* bt)
{
	buildingHold->push_back(bt);
	*numOfBuilding = *numOfBuilding + 1;
}

int Hand::getNodeID(GBMap* gb_map, int row, int col)
{
	int height = gb_map->getTileGraph()->getHeight();
	int length = gb_map->getTileGraph()->getHeight();
	return (row * length + col);
}

bool Hand::requestRotate(HarvestTile* target)
{
	std::cout << "\n---Start rotating session---" << std::endl;

	char input;
	char back = 'b';
	char end = 'e';
	char rotate = 'r';

	while (true) {
		std::cout << "\n---------------" << std::endl;
		std::cout << "Your Harvest Tile:" << std::endl;
		std::cout << *target << std::endl;
		std::cout << "---------------" << std::endl;
		
		std::cout << "+ Rotate the Tile: r" << std::endl;
		std::cout << "+ End rotating the Tile: e" << std::endl;
		std::cout << "+ Choose another Tile: b" << std::endl;
		std::vector<ResourceType>* container = target->getContainer();

		try {
			std::cin >> input;

			if (input == back) {
				return false;
			}

			if (input == end) {
				std::cout << "------------------------------------------" << std::endl;
				std::cout << "Placing Tile on the gameboard" << std::endl;
				std::cout << "------------------------------------------" << std::endl;
				return true;

			}

			if (input == rotate) {
				// Mimic a deque for rotating clockwise 
				std::cout << "Rotating ..." << std::endl;
				ResourceType temp = container[0][3];
				container[0].insert(container[0].begin(), temp);
				container[0].erase(container[0].end() - 1);
				continue;
			}

			throw std::exception();
		}
		catch (const std::exception & e) {
			std::cout << "Invalid input. Please try again" << std::endl;
			continue;
		}

	}

}

void Hand::exchange(GBMap* gb_map, HarvestTile* target, TileNode* location)
{
	std::map<ResourceType, int> resourcesCollected = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };
	gb_map->calcResourceAdjacencies(location, resourcesCollected);

	// Print out the resources collected
	std::cout << "\nGenerated Resources:" << std::endl;
	std::cout << "SHEEP: " << resourcesCollected[ResourceType::SHEEP] << std::endl;
	std::cout << "STONE: " << resourcesCollected[ResourceType::STONE] << std::endl;
	std::cout << "TIMBER: " << resourcesCollected[ResourceType::TIMBER] << std::endl;
	std::cout << "WHEAT: " << resourcesCollected[ResourceType::WHEAT] << std::endl;

}

int Hand::playHarvest(GBMap* gb_map) {
	std::cout << "\n----PLAYING HARVEST TILE----" << std::endl;
	while (true) {
		if (hasNoHarvest()) {
			std::cout << "There is no Harvest Tile on hand to play" << std::endl;
			return 1;
		}

		showHand();

		//Ask for choice of Harvest Tile on hand
		int choice = -1;
		std::cout << "\nCurrently, you are having " << getRemainHarvest() << " Harvest Tiles on your hand" << std::endl;
		std::cout << "Please enter the index of Harvest Tile you want to play" << std::endl;
		try {
            std::cin >> choice;
            if (choice < 0 || choice >= this->getRemainHarvest()) {
                throw std::exception();
            }

		} catch (const std::exception& e) {
		    std::cout << "Invalid choice. Please try again." << std::endl;
		    continue;
		}

		HarvestTile* target = getHarvestTile(choice);

		//Ask for position on the map to place tile
		std::cout << "\n---Select position to place Tile---" << std::endl;
		int row, col;
		try {
			std::cout << "Enter the index of row:" << std::endl;
			std::cin >> row;
			if (row < 0 || row >= gb_map->getTileGraph()->getHeight()) {
				throw std::exception();
			}

			std::cout << "Enter the index of column:" << std::endl;
			std::cin >> col;
			if (col < 0 || col >= gb_map->getTileGraph()->getLength()) {
				throw std::exception();
			}
		}
		catch (const std::exception & e) {
			std::cout << "Invalid position input. Please try again" << std::endl;
			continue;
		}

		/* Check if the position is enabled and not occupied
		=> process to rotate the Tile as requested
		=> Place Tile on the map and calculate resources by exchange
		*/
		int nodeID = this->getNodeID(gb_map, row, col);
		TileNode* location = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(nodeID));
		if (gb_map->isValid(location)) {
			if (requestRotate(target)) {
				// User satisfies with their choice of rotation, process to place HarvestTile
				gb_map->placeHarvestTile(target, location);
				std::cout << "\nPLACED TILE ON THE GAMEBOARD SUCCESSFULLY\n" << std::endl;
				exchange(gb_map, target, location);
				break;
			}

		}
		else {
			std::cout << "\n------------------------------------------" << std::endl;
			std::cout << "The position is either occupied or invalid" << std::endl;
			std::cout << "Please try again." << std::endl;
			std::cout << "------------------------------------------\n" << std::endl;
			continue;
		}
	}

	return 0;
}
