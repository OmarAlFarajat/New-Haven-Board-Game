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