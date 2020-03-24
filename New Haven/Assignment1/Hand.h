#pragma once
#include <map>
#include <vector>
#include "GBMap.h"
#include "Harvest.h"
#include "Building.h"
#include "VGMap.h"

using std::vector;

// Hand Object 
class Hand 
{
	int* numOfHarvest;
	int* numOfBuilding;
	bool* containSHIPMENT;
	HarvestTile* SHIPMENT_TILE;
	vector<HarvestTile*>* harvestHold;
	vector<BuildingTile*>* buildingHold;

	public:
	Hand();
	~Hand();

	int getRemainHarvest();
	int getRemainBuilding();
	bool hasNoHarvest();
	bool hasNoBuilding();
	HarvestTile* getSHIPMENT_TILE();
	bool hasSHIPMENT_TILE();
	vector<HarvestTile*>* getHarvestHold();
	vector<BuildingTile*>* getBuildingHold();
	HarvestTile* getHarvestTile(int index);
	BuildingTile* getBuildingTile(int index);

	void showHarvests();
	void showBuildings();
	void showHand();
	void addSHIPMENT(HarvestTile* shipment);
	void addHarvestTile(HarvestTile* ht);
	void addBuildingTile(BuildingTile* bt);
	int getNodeID_GB(GBMap* gb_map, int row, int col);
	int getNodeID_VG(VGMap* vg_map, int row, int col);

	void playSHIPMENT();

	void exchange(GBMap* gb_map, TileNode*);
	bool requestRotate(HarvestTile* target);
	int playHarvest(GBMap* gb_map);

	bool requestFlip(BuildingTile* target);
	void playBuilding(VGMap* vg_map);

};

inline int Hand::getRemainHarvest() {return *numOfHarvest;}
inline int Hand::getRemainBuilding() {return *numOfBuilding;}
inline bool Hand::hasNoHarvest() {return (*numOfHarvest == 0);}
inline bool Hand::hasSHIPMENT_TILE() { return *containSHIPMENT; }
inline bool Hand::hasNoBuilding() { return (*numOfBuilding == 0);}
inline HarvestTile* Hand::getSHIPMENT_TILE() { return SHIPMENT_TILE; }
inline vector<HarvestTile*>* Hand::getHarvestHold() { return harvestHold; }
inline vector<BuildingTile*>* Hand::getBuildingHold() { return buildingHold; }
inline HarvestTile* Hand::getHarvestTile(int index) {return harvestHold[0][index];}
inline BuildingTile* Hand::getBuildingTile(int index) { return buildingHold[0][index]; }

