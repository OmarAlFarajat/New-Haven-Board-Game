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

	buildingsAvailable[0] = new BuildingTile();
	buildingsAvailable[1] = new BuildingTile();
	buildingsAvailable[2] = new BuildingTile();
	buildingsAvailable[3] = new BuildingTile();
	buildingsAvailable[4] = new BuildingTile();

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
	return(!tileNode->isOccupied() && tileNode->isEnabled());
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

