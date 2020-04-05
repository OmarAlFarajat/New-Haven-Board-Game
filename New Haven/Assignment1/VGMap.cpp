#include "VGMap.h"

using std::cout;
using std::endl;

VGMap::VGMap()
{
	name = new string();
	buildingGraph = new Graph();
	firstPlacementExisted = new vector<bool*>;
	for (int i = 0; i < 4; ++i) {
		firstPlacementExisted->push_back(new bool(false));
	}
}

VGMap::~VGMap()
{
	delete name;
	name = nullptr;
	delete buildingGraph;
	buildingGraph = nullptr;
	delete[] firstPlacementExisted;
	firstPlacementExisted = nullptr;
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

void VGMap::setFirstPlacement(ResourceType type)
{
	switch (type) {
	case ResourceType::TIMBER:
		*firstPlacementExisted[0][0] = new bool(true);
		break;
	case ResourceType::STONE:
		*firstPlacementExisted[0][1] = new bool(true);
		break;
	case ResourceType::WHEAT:
		*firstPlacementExisted[0][2] = new bool(true);
		break;
	case ResourceType::SHEEP:
		*firstPlacementExisted[0][3] = new bool(true);
		break;
	}
}

bool VGMap::isFirstPlacement(ResourceType type)
{
	switch (type) {
	case ResourceType::TIMBER:
		return !*firstPlacementExisted->at(0);
	case ResourceType::STONE:
		return !*firstPlacementExisted->at(1);
	case ResourceType::WHEAT:
		return !*firstPlacementExisted->at(2);
	case ResourceType::SHEEP:
		return !*firstPlacementExisted->at(3);
	}
}

bool VGMap::isAdjacent(ResourceType const fromHand, BuildingTile* const toBoard)
{
	// Edge exists (not null)		... the neighbouring node is of the board space has a building that is of the same type as that being placed from the hand
	bool evaluate =(toBoard->getUp() &&	static_cast<BuildingTile*>(toBoard->getUp())->getType() == fromHand) ||
				(toBoard->getDown()	&&	static_cast<BuildingTile*>(toBoard->getDown())->getType() == fromHand)	||
				(toBoard->getLeft()	&&	static_cast<BuildingTile*>(toBoard->getLeft())->getType() == fromHand)	||
				(toBoard->getRight() &&	static_cast<BuildingTile*>(toBoard->getRight())->getType() == fromHand);
	return evaluate;
}

bool VGMap::isValid(BuildingTile* fromHand, BuildingTile* toBoard) {
	// Check all building nodes to see if this type of building has been placed before. 

	bool firstPlacementOfType = isFirstPlacement(fromHand->getType()); 

	// If playing face down, only check if space is not occupied, node is enabled, and is adjacent
	if (!fromHand->isFaceUp()) {
		// If it is the first placement, then check if enabled and not occupied.
		if (firstPlacementOfType) {
			//cout << ">>> First placement of type "<< endl;
			return !toBoard->isOccupied() && toBoard->isEnabled();
		}
		// If it is not the first placement of that type, then check that at least one adjacent node is of the same type
		else {
			//cout << ">>> Not first placement of type, validating extra requirements..." << endl; 
			return !toBoard->isOccupied() && toBoard->isEnabled() 
				&& isAdjacent(fromHand->getType(), toBoard);
		}
	}

	// The rest of the logic assumes that the building requesting to be played is face up
	cout << ">>> Building is face up... " << endl;

	// If it is the first placement, then check if enabled and not occupied and the value of the building matches the value of the space
	if (firstPlacementOfType) {
		//cout << ">>> First placement of type, checking if same value..." << endl;
		return !toBoard->isOccupied() && toBoard->isEnabled() 
			&& (toBoard->getValue() == fromHand->getValue());
	}
	// If it is not the first placement of that type, then check that at least one adjacent node is of the same type
	else {
		//cout << ">>> Not first placement of type, checking if adjacent..." << endl; 
		return !toBoard->isOccupied() && toBoard->isEnabled() 
			&& (toBoard->getValue() == fromHand->getValue())
			&& isAdjacent(fromHand->getType(), toBoard);
	}
}

void VGMap::placeBuildingTile(BuildingTile* fromHand, BuildingTile* toBoard) {
	toBoard->setValue(fromHand->getValue());
	toBoard->setType (fromHand->getType());
	toBoard->setFaceUp(fromHand->isFaceUp());	
	toBoard->setOccupied(true);
	if (isFirstPlacement(fromHand->getType())) {
		setFirstPlacement(fromHand->getType());
	}
}

int VGMap::calculatePoints() {

	int points = 0; 
	int buildingCount = 0; 

	//// Calculate points for each row
	bool perfectRow = true; 
	int colonistRowValue[6] = {6,5,4,3,2,1};

	// j is the row number
	for (int j = 0; j < buildingGraph->getHeight(); j++) {

		// i is the column number respective to each row.
		for (int i = 0; i < buildingGraph->getLength(); i++) {

			int calculatedID = i + j * buildingGraph->getLength(); 

			if (buildingGraph->getNode(calculatedID)->isOccupied())
				buildingCount++;

			if (!static_cast<BuildingTile*>(buildingGraph->getNode(calculatedID))->isFaceUp())
				perfectRow = false;

			if (buildingCount == buildingGraph->getLength()) 
				if (perfectRow) {
					cout << "~~~ Found a perfect row! " << 2 * colonistRowValue[j] << endl;
					points += 2 * colonistRowValue[j];
				}
				else {
					cout << "~~~ Found an imperfect row! " << colonistRowValue[j] << endl;
					points += colonistRowValue[j];
				}
			
		}

		perfectRow = true;
		buildingCount = 0; 
	}

	//// Calculate points for each column
	bool perfectColumn = true;
	int colonistColumnValue[5] = { 5,4,3,4,5 };

	// j is the column number
	for (int j = 0; j < buildingGraph->getLength(); j++) {

		// i is the row number respective to each column.
		for (int i = 0; i < buildingGraph->getHeight(); i++) {

			int calculatedID = j + i * buildingGraph->getLength();

			if (buildingGraph->getNode(calculatedID)->isOccupied())
				buildingCount++;

			if (!static_cast<BuildingTile*>(buildingGraph->getNode(calculatedID))->isFaceUp())
				perfectRow = false;

			if (buildingCount == buildingGraph->getHeight())
				if (perfectRow) {
					cout << "~~~ Found a perfect column! " << 2 * colonistColumnValue[j] << endl;
					points += 2 * colonistColumnValue[j];
				}
				else {
					cout << "~~~ Found an imperfect column! " << colonistColumnValue[j] << endl;
					points += colonistColumnValue[j];
				}
		}
		perfectRow = true;
		buildingCount = 0;
	}
	

	return points;
}