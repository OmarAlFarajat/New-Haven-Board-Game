#include "VGMap.h"

VGMap::VGMap()
{
	name = new std::string();
	buildingGraph = new Graph();
}

VGMap::~VGMap()
{
}

bool VGMap::isValid(BuildingTile* buildingTile) {
	return(!buildingTile->isOccupied() && buildingTile->isEnabled());
}

void VGMap::placeBuildingTile(BuildingTile* fromHand, BuildingTile* toBoard) {
	toBoard->setValue(fromHand->getValue());
	toBoard->setType (fromHand->getType());
	toBoard->setOccupied(true);
}

int VGMap::calculatePoints() {

	int points = 0; 
	int buildingCount = 0; 

	bool perfectRow = true; 
	int colonistRowValue[6] = {6,5,4,3,2,1};

	// j is the row number
	for (int j = 0; j < buildingGraph->getHeight(); j++) {

		// i is the column number respective to each row.
		for (int i = 0; i < buildingGraph->getLength(); i++) {

			if (buildingGraph->getNode(i + j* buildingGraph->getLength())->isOccupied())
				buildingCount++;

			if (!static_cast<BuildingTile*>(buildingGraph->getNode(i + j * buildingGraph->getLength()))->getFaceUp())
				perfectRow = false;

			if (buildingCount == buildingGraph->getLength()) 
				if (perfectRow) {
					std::cout << "~~~ Found a perfect row! " << 2 * colonistRowValue[j] << std::endl;
					points += 2 * colonistRowValue[j];
				}
				else {
					std::cout << "~~~ Found an imperfect row! " << colonistRowValue[j] << std::endl;
					points += colonistRowValue[j];
				}
			
		}

		perfectRow = true;
		buildingCount = 0; 
	}

	bool perfectColumn = true;
	int colonistColumnValue[5] = { 5,4,3,4,5 };

	// j is the column number
	for (int j = 0; j < buildingGraph->getLength(); j++) {

		// i is the row number respective to each column.
		for (int i = 0; i < buildingGraph->getHeight(); i++) {
			if (buildingGraph->getNode(j + i * buildingGraph->getLength())->isOccupied())
				buildingCount++;

			if (!static_cast<BuildingTile*>(buildingGraph->getNode(j + i * buildingGraph->getLength()))->getFaceUp())
				perfectRow = false;

			if (buildingCount == buildingGraph->getHeight())
				if (perfectRow) {
					std::cout << "~~~ Found a perfect column! " << 2 * colonistColumnValue[j] << std::endl;
					points += 2 * colonistColumnValue[j];
				}
				else {
					std::cout << "~~~ Found an imperfect column! " << colonistColumnValue[j] << std::endl;
					points += colonistColumnValue[j];
				}

		}

		perfectRow = true;
		buildingCount = 0;
	}
	

	return points;
}