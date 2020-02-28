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
	int length = gb_map->getTileGraph()->getLength();
	return (row * length + col);
}

int Hand::getNodeID_VG(VGMap* vg_map, int row, int col)
{
	int length = vg_map->getBuildingGraph()->getLength();
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

void Hand::exchange(GBMap* gb_map, TileNode* location)
{
    std::map<ResourceType , int> generatedResources = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };
	gb_map->calcResourceAdjacencies(location, generatedResources);
	gb_map->setResourceTracker(&generatedResources);
	gb_map->displayResourceTracker();
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
				exchange(gb_map, location);
				harvestHold->erase(harvestHold[0].begin() + choice); //Remove the tile from hand after placement
				*numOfHarvest = *numOfHarvest - 1;
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


bool Hand::requestFlip(BuildingTile* target) {
    std::cout << "\n---Start flipping---" << std::endl;

    char input;
    char back = 'b';
    char end = 'e';
    char flip = 'f';
    char question = '?';

    while (true) {
        std::cout << "\n---------------" << std::endl;
        std::cout << "Your Building Tile:" << std::endl;
        std::cout << *target << std::endl;
        std::cout << "---------------" << std::endl;

        std::cout << "+ Flip the Tile: f" << std::endl;
        std::cout << "+ End flipping the Tile: e" << std::endl;
        std::cout << "+ Choose another Tile: b" << std::endl;
        std::cout << "+ Trade-of of flipping request: ?" << std::endl;

        try {
            std::cin >> input;

            if (input == back) {
                return false;
            }

            if (input == end) {
                std::cout << "------------------------------------------" << std::endl;
                std::cout << "Validating the request" << std::endl;
                std::cout << "------------------------------------------" << std::endl;
                return true;

            }

            if(input == question) {
                std::cout << "----OVERVIEW----" << std::endl;
                std::cout << "\nBuildings may only be played face up if the number on the\n"
                             "\t space matches the number showing on the Building." << std::endl;
                std::cout << "\nBuildings may be played face down onto any number space,\n"
                             "\t regardless of the number on the Building." << std::endl;
                std::cout << "\nThe value of each row and column is the number\n"
                             "of Colonists shown at the right or bottom. BUT! The value of a row or column is doubled if every\n"
                             "Building played on that row or column is face up!" << std::endl;
                continue;
            }

            if(input == flip) {
                std::cout << "\nFlipping the tile" << std::endl;
                target->setFaceUp(!target->getFaceUp());
                if(target->getFaceUp()) {
                    std::cout << "The Building Tile is faced up." << std::endl;
                    std::cout << "You CAN earn double points if you complete the whole column or row corresponding to the position of this card" << std::endl;
                } else {
                    std::cout << "The Building Tile is faced down." << std::endl;
                    std::cout << "You CANNOT earn double points if you complete the whole column or row corresponding to the position of this card" << std::endl;
                }
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

void Hand::playBuilding(VGMap* vg_map) {
	std::cout << "\n----PLAYING BUILDING TILE----" << std::endl;
	while (true) {
		if (hasNoBuilding()) 
			std::cout << "There is no Building Tile on hand to play" << std::endl;
		
		showHand();

		//Ask for choice of Building Tile from hand
		int choice = -1;
		std::cout << "\nCurrently, you have " << getRemainBuilding() << " Building tiles in your hand" << std::endl;
		std::cout << "Please enter the index of Building Tile you want to play" << std::endl;
		try {
			std::cin >> choice;
			if (choice < 0 || choice >= this->getRemainBuilding()) {
				throw std::exception();
			}

		}
		catch (const std::exception & e) {
			std::cout << "Invalid choice. Please try again." << std::endl;
			continue;
		}

		BuildingTile* target = getBuildingTile(choice);

		//Ask for position on the map to place tile
		std::cout << "\n---Select position to place Tile---" << std::endl;
		int row, col;
		try {
			std::cout << "Enter the index of row:" << std::endl;
			std::cin >> row;
			if (row < 0 || row >= vg_map->getBuildingGraph()->getHeight()) {
				throw std::exception();
			}

			std::cout << "Enter the index of column:" << std::endl;
			std::cin >> col;
			if (col < 0 || col >= vg_map->getBuildingGraph()->getLength()) {
				throw std::exception();
			}
		}
		catch (const std::exception & e) {
			std::cout << "Invalid position input. Please try again" << std::endl;
			continue;
		}

		/* Check if the position is enabled and not occupied
		=> process to flip the tile as requested
		=> Place Tile on the map.
		*/
		int nodeID = this->getNodeID_VG(vg_map, row, col);
		BuildingTile* location = static_cast<BuildingTile*>(vg_map->getBuildingGraph()->getNode(nodeID));
		if (requestFlip(target)) {
		    if(vg_map->isValid(target, location)) {
                vg_map->placeBuildingTile(target, location);
                std::cout << "\nPLACED TILE ON THE VGBOARD SUCCESSFULLY\n" << std::endl;
                buildingHold->erase(buildingHold[0].begin() + choice); //Remove the tile from hand after placement
                *numOfBuilding = *numOfBuilding - 1;
                break;
		    } else {
                std::cout << "\n------------------------------------------" << std::endl;
                std::cout << "The position is either occupied or invalid flipping request" << std::endl;
                std::cout << "Please try again." << std::endl;
                std::cout << "------------------------------------------\n" << std::endl;
                continue;
            }
		}

	}
}

