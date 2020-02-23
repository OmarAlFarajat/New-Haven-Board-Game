#include "Hand.h"

hand::hand()
{
}

hand::~hand()
{
}

void rotateRequest(HarvestTile* target) {
}

void Hand::exchange(GBMap* gb_map)
{


}

int Hand::playHarvest(GBMap* gb_map) {
	while(true) {
		std::cout << "Currently, you are having " << this->getRemainHarvest() << " Harvest Tiles on your hand" << std::endl;
		if(hasNoHarvest()) {
			std::cout << "There is no Harvest Tile on hand to play" << std::endl;
			return 1;
		}

		std::cout << "Displaying your Harvest Tiles" << std::endl;

		for(int i = 0; i< this->getRemainHarvest(); ++i) {
			std::cout << "Tile no." << i << std::endl;
			std::cout << this->harvestHold[0][i] << std::endl;
		}
		
		int choice;
		std::cout << "Please enter the index of Harvest Tile you want to play" << std::endl;
		std::cin >> choice;
		if (choice < 0 || choice >= this->getRemainHarvest()) {
			std::cout << "Invalid choice. Please try again." << std::endl;
			continue;
		}

		HarvestTile* target = this->getHarvestTile(choice);
		int row, col;
		std::cout << "Please enter the row index (starting from 0):" << std::endl;
		std::cin >> row;
		std::cout << "Please enter the column index (starting from 0):" << std::endl;
		std::cin >> col;
		
		//TODO: check for validity of the requested position
		/*
		 * For now, the temp variable is a test with node index 7
		 */
		TileNode* temp = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(7));
		if(gb_map->isValid(temp)) {
			rotateRequest(target);	
			exchange(gb_map);
			break;
		} else {
			std::cout << "The position is either occupied or invalid" << std::endl;
			std::cout << "Please try again." << std::endl;
			continue;
		}
	}

	return 0;
}


