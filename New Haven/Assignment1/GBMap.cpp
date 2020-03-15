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
	delete resourceGraph;
	delete resourceTracker; 
	// TODO: Causes errors
	//delete[] buildingsAvailable;

}

void GBMap::setResourceTracker(std::map<ResourceType, int>* inTracker)
{
	resourceTracker[0][ResourceType::SHEEP] = inTracker[0][ResourceType::SHEEP];
	resourceTracker[0][ResourceType::STONE] = inTracker[0][ResourceType::STONE];
	resourceTracker[0][ResourceType::TIMBER] = inTracker[0][ResourceType::TIMBER];
	resourceTracker[0][ResourceType::WHEAT] = inTracker[0][ResourceType::WHEAT];

}

void GBMap::displayResourceTracker()
{
	cout << "GBMap RESOURCE TRACKER: " << endl;
	cout << "SHEEP: " << resourceTracker[0][ResourceType::SHEEP] << endl;
	cout << "TIMBER: " << resourceTracker[0][ResourceType::TIMBER] << endl;;
	cout << "STONE: " << resourceTracker[0][ResourceType::STONE] << endl;;
	cout << "WHEAT: " << resourceTracker[0][ResourceType::WHEAT] << endl;;

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
	tileNode->getResourceNodes()[0]->setType(harvestTile->getResources()[0]);
	tileNode->getResourceNodes()[0]->setOccupied(true);

	tileNode->getResourceNodes()[1]->setType(harvestTile->getResources()[1]);
	tileNode->getResourceNodes()[1]->setOccupied(true);

	tileNode->getResourceNodes()[2]->setType(harvestTile->getResources()[3]);
	tileNode->getResourceNodes()[2]->setOccupied(true);

	tileNode->getResourceNodes()[3]->setType(harvestTile->getResources()[2]);
	tileNode->getResourceNodes()[3]->setOccupied(true);

	return true;
}

