#include "GBMap.h"
#include "Harvest.h"

GBMap::GBMap()
{
	tileGraph = new Graph();
	resourceGraph = new Graph(); 
}

GBMap::~GBMap()
{
}

void GBMap::calcResourceAdjacencies(TileNode* root, std::map<ResourceType, int> &output)
{
	resourceGraph->DFS_ByType(root->getResourceNodes()[0]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[1]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[2]);
	resourceGraph->DFS_ByType(root->getResourceNodes()[3]);



		for (int i = 0; i < resourceGraph->getNumEnabledNodes(); i++) {
			if (resourceGraph->getNode(i)->isVisited()) {

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
	


	resourceGraph->resetAllVisited();
}

bool GBMap::isValid(TileNode* tileNode) {
	return(!tileNode->isOccupied() && tileNode->isEnabled());
}

bool GBMap::placeHarvestTile(HarvestTile* harvestTile, TileNode* tileNode) {
	tileNode->getResourceNodes()[0]->setType(harvestTile->getResources()[0]);
	tileNode->getResourceNodes()[1]->setType(harvestTile->getResources()[1]);
	tileNode->getResourceNodes()[2]->setType(harvestTile->getResources()[3]);
	tileNode->getResourceNodes()[3]->setType(harvestTile->getResources()[2]);

	return true;
}

