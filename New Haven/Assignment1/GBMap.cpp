#include<algorithm>
#include "GBMap.h"
#include "Harvest.h"

using std::cout;
using std::cin;
using std::endl;

GBMap::GBMap()
{
	tileGraph = new Graph();
	resourceGraph = new Graph(); 

	resourceTracker = new std::map<ResourceType,int>;
	resourceTracker[0] = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };

	buildingsAvailable[0] = nullptr;
	buildingsAvailable[1] = nullptr;
	buildingsAvailable[2] = nullptr;
	buildingsAvailable[3] = nullptr;
	buildingsAvailable[4] = nullptr;

	isSideB = new bool(false);

}

GBMap::~GBMap()
{
	delete tileGraph;
	tileGraph = nullptr;
	delete resourceGraph;
	resourceGraph = nullptr;
	delete resourceTracker; 
	resourceTracker = nullptr;
	for (auto each : buildingsAvailable) {
		delete each;
		each = nullptr;
	}
	// TODO: Causes errors
	//delete[] buildingsAvailable;

}

bool GBMap::GameOver()
{
	int counter = 0;
	for (int i = 0; i < tileGraph->getNodes()[0].size(); i++)
		if (tileGraph->getNodes()[0][i]->isOccupied())
			counter++;
	if (counter == tileGraph->getNumEnabledNodes() - 1)
		return true;
	return false;
}

void GBMap::setResourceTracker(std::map<ResourceType, int>* inTracker)
{
	resourceTracker[0][ResourceType::SHEEP] = inTracker[0][ResourceType::SHEEP];
	resourceTracker[0][ResourceType::STONE] = inTracker[0][ResourceType::STONE];
	resourceTracker[0][ResourceType::TIMBER] = inTracker[0][ResourceType::TIMBER];
	resourceTracker[0][ResourceType::WHEAT] = inTracker[0][ResourceType::WHEAT];

}

void GBMap::spendResource(ResourceType type, int cost)
{
	resourceTracker[0][type] -= cost;
}

bool GBMap::isValidExpense(ResourceType type, int cost)
{
	return (resourceTracker[0][type] >= cost);
}

bool GBMap::hasWealthToShare()
{
	return (resourceTracker[0][ResourceType::SHEEP] > 0) ||
		(resourceTracker[0][ResourceType::STONE] > 0) ||
		(resourceTracker[0][ResourceType::TIMBER] > 0) ||
		(resourceTracker[0][ResourceType::WHEAT] > 0) ;
}

void GBMap::displayResourceTracker()
{
	cout << ">>> Resource Tracker " << endl;
	cout << "\tSHEEP: " << resourceTracker[0][ResourceType::SHEEP] << endl;
	cout << "\tTIMBER: " << resourceTracker[0][ResourceType::TIMBER] << endl;;
	cout << "\tSTONE: " << resourceTracker[0][ResourceType::STONE] << endl;;
	cout << "\tWHEAT: " << resourceTracker[0][ResourceType::WHEAT] << "\n" << endl;;

}

void GBMap::calcResourceAdjacencies(TileNode* root, std::map<ResourceType, int> &output)
{
	// Recursive calls
	resourceGraph->DFS_ByType(root->getResourceNodes()[0]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[1]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[2]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[3]);

	// Iterates through all Resource nodes in the resource graph
		for (int i = 0; i < resourceGraph->getNumEnabledNodes(); i++) {
			// If the node is marked as visited...
			if (resourceGraph->getNode(i)->isVisited()) {
				// ...then increment the amount accumulated of the given ResourceType
				switch (static_cast<Resource*>(resourceGraph->getNode(i))->getType()) {

				case ResourceType::SHEEP:
					output[ResourceType::SHEEP]++;
					break;
				case ResourceType::STONE:
					output[ResourceType::STONE]++;
					break;
				case ResourceType::WHEAT:
					output[ResourceType::WHEAT]++;
					break;
				case ResourceType::TIMBER:
					output[ResourceType::TIMBER]++;
					break;
				}
			}

		}
	// Reset the state of all nodes to unvisited
	resourceGraph->resetAllVisited();
}

bool GBMap::isValid(TileNode* tileNode) {
	return(!tileNode->isOccupied() && tileNode->isEnabled() || tileNode->isBuildingTile());
}

bool GBMap::placeHarvestTile(HarvestTile* harvestTile, TileNode* tileNode) {
	if (harvestTile->isShipmentTile()) {
		for (int i = 0; i < harvestTile->getNumOfResource(); ++i) {
			tileNode->getResourceNodes()[i]->setType(*harvestTile->getShipmentContainer()[i]);
			tileNode->getResourceNodes()[i]->setOccupied(true);
		}
		tileNode->setOccupied(true);
		tileNode->setShipmentStatus(true);
		return true;
	}

	tileNode->getResourceNodes()[0]->setType(harvestTile->getContainer()[0]);
	tileNode->getResourceNodes()[1]->setType(harvestTile->getContainer()[1]);
	tileNode->getResourceNodes()[2]->setType(harvestTile->getContainer()[3]);
	tileNode->getResourceNodes()[3]->setType(harvestTile->getContainer()[2]);

	tileNode->getResourceNodes()[0]->setOccupied(true);
	tileNode->getResourceNodes()[1]->setOccupied(true);
	tileNode->getResourceNodes()[2]->setOccupied(true);
	tileNode->getResourceNodes()[3]->setOccupied(true);

	tileNode->setShipmentStatus(false);
	tileNode->setOccupied(true);

	return true;
}

bool GBMap::placeBuildingTile(BuildingTile* building, TileNode* tileNode)
{
	if (!tileNode->isEnabled()) {
		return false;
	}
	tileNode->setBuildingStatus(true);
	tileNode->setOccupied(true);
	//Set occupied but not setting the type
	for (int i = 0; i < 4; ++i) {
		tileNode->getResourceNodes()[i]->setOccupied(true);
	}
}

BuildingTile* GBMap::DrawBuilding(BuildingDeck* deck)
{
	if (deck->getNumOfRemain() <= 0) {
		cout << "There is no more Building Tile in the Deck to draw" << endl;
		return nullptr; 
	}
	else {
		return deck->draw();
	}
}

HarvestTile* GBMap::DrawHarvest(HarvestDeck* deck) {
	if (deck->getNumOfRemain() <= 0) {
		cout << "There is no more Harvest Tile in the Deck to draw" << endl;
		return nullptr; 
	}
	else {
		return deck->draw();
	}
}

HarvestTile* GBMap::DrawPond() {
	HarvestTile* temp = new HarvestTile();
	temp->becomesPond();
	return temp;
}

void GBMap::initSettlementLocation() {
	this->settlementLocation[0].push_back(8);
	this->settlementLocation[0].push_back(10);
	this->settlementLocation[0].push_back(12);

	this->settlementLocation[0].push_back(22);
	this->settlementLocation[0].push_back(26);

	this->settlementLocation[0].push_back(36);
	this->settlementLocation[0].push_back(38);
	this->settlementLocation[0].push_back(40);
}

void GBMap::initBuildingLocation() {
	this->buildingLocation[0].push_back(2);
	this->buildingLocation[0].push_back(4);

	this->buildingLocation[0].push_back(14);
	this->buildingLocation[0].push_back(16);
	this->buildingLocation[0].push_back(18);
	this->buildingLocation[0].push_back(20);

	this->buildingLocation[0].push_back(24);

	this->buildingLocation[0].push_back(28);
	this->buildingLocation[0].push_back(30);
	this->buildingLocation[0].push_back(32);
	this->buildingLocation[0].push_back(34);

	this->buildingLocation[0].push_back(44);
	this->buildingLocation[0].push_back(46);
}

void GBMap::makeSideB(BuildingDeck* buildDeck, HarvestDeck* harvestDeck) {
	*isSideB = true;

	initBuildingLocation();
	//Place settlements buildings on the board
	for (int i = 0; i < getBuildingLocation().size(); ++i) {
		TileNode* location = static_cast<TileNode*>(this->getTileGraph()->getNode(getBuildingLocation()[i]));
		BuildingTile* building = DrawBuilding(buildDeck);
		if (!location->isEnabled()){
			placeBuildingTile(building, location);
		}
	}

	initSettlementLocation();
	vector<HarvestTile*> pondAndHarvest;
	// Add Harvest Tiles and Pond Tiles
	int turn = 4;
	for (int i = 0; i < turn; ++i) {
		pondAndHarvest.push_back(DrawHarvest(harvestDeck));
		pondAndHarvest.push_back(DrawPond());
	}

	random_shuffle(pondAndHarvest.begin(), pondAndHarvest.end()); 

	//Place ponds and init harvest tile on the board
	for (int i = 0; i < getSettlementLocation().size(); ++i) {
		TileNode* location = static_cast<TileNode*>(this->getTileGraph()->getNode(getSettlementLocation()[i]));
		placeHarvestTile(pondAndHarvest[i], location);
	}
}
