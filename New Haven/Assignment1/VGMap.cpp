#include "VGMap.h"

VGMap::VGMap()
{
	name = new std::string();
	buildingGraph = new Graph();
}

VGMap::~VGMap()
{
}

void VGMap::initTileValues() {
	for (Node* x : buildingGraph->getNodes()[0]){
		if (x->getID() < 5)
			static_cast<BuildingTile*>(x)->setValue(6);
		else if (x->getID() < 10)
			static_cast<BuildingTile*>(x)->setValue(5);
		else if (x->getID() < 15)
			static_cast<BuildingTile*>(x)->setValue(4);
		else if (x->getID() < 20)
			static_cast<BuildingTile*>(x)->setValue(3);
		else if (x->getID() < 25)
			static_cast<BuildingTile*>(x)->setValue(2);
		else if (x->getID() < 30)
			static_cast<BuildingTile*>(x)->setValue(1);
	}
}

bool VGMap::isValid(BuildingTile* fromHand, BuildingTile* toBoard) {

	// If playing face down, only check if space is not occupied, and the node is enabled.
	if (!fromHand->getFaceUp())
		return !toBoard->isOccupied() && toBoard->isEnabled();

	// The rest of the logic assumes that the building requesting to be played is face up
	std::cout << ">>> Building is face up... " << std::endl;

	// Check all building nodes to see if this type of building has been placed before. 
	bool firstPlacementOfType = true; 
	for (Node* x : buildingGraph->getNodes()[0]) 
		if (static_cast<BuildingTile*>(x)->getType() == fromHand->getType()) {
			std::cout << ">>> Not the first placement... " << std::endl;
			firstPlacementOfType = false;
		}
	// If it is the first placement, then check if enabled and not occupied and the value of the building matches the value of the space
	if (firstPlacementOfType) {
		std::cout << ">>> First placement of type, checking if same value..." << std::endl;
		return !toBoard->isOccupied() && toBoard->isEnabled() && (toBoard->getValue() == fromHand->getValue());
	}
	// If it is not the first placement of that type, then check that at least one adjacent node is of the same type
	else {
		std::cout << ">>> Not first placement of type, checking if adjacent..." << std::endl; 
		return !toBoard->isOccupied() && toBoard->isEnabled() && (toBoard->getValue() == fromHand->getValue()) &&
				// Edge exists (not null)		... the neighbouring node is of the board space has a building that is of the same type as that being placed from the hand
			(	(toBoard->getUp()		&&		static_cast<BuildingTile*>(toBoard->getUp())->getType() == fromHand->getType())		||
				(toBoard->getDown()		&&		static_cast<BuildingTile*>(toBoard->getDown())->getType() == fromHand->getType())	||
				(toBoard->getLeft()		&&		static_cast<BuildingTile*>(toBoard->getLeft())->getType() == fromHand->getType())	||
				(toBoard->getRight()	&&		static_cast<BuildingTile*>(toBoard->getRight())->getType() == fromHand->getType())	);
	}
}

void VGMap::placeBuildingTile(BuildingTile* fromHand, BuildingTile* toBoard) {
	toBoard->setValue(fromHand->getValue());
	toBoard->setType (fromHand->getType());
	toBoard->setFaceUp(fromHand->getFaceUp());	
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