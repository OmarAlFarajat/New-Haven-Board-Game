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
	vector<HarvestTile*>* harvestHold;
	vector<BuildingTile*>* buildingHold;

	public:
	Hand();
	~Hand();

	int getRemainHarvest();
	int getRemainBuilding();
	bool hasNoHarvest();
	bool hasNoBuilding();

	HarvestTile* getHarvestTile(int index);
	BuildingTile* getBuildingTile(int index);

	void showHand();
	void addHarvestTile(HarvestTile* ht);
	void addBuildingTile(BuildingTile* bt);
	int getNodeID_GB(GBMap* gb_map, int row, int col);
	int getNodeID_VG(VGMap* vg_map, int row, int col);

  void exchange(GBMap* gb_map, TileNode*);
	bool requestRotate(HarvestTile* target);
	int playHarvest(GBMap* gb_map);

	bool requestFlip(BuildingTile* target);
	void playBuilding(VGMap* vg_map);

};

inline int Hand::getRemainHarvest() {return *numOfHarvest;}
inline int Hand::getRemainBuilding() {return *numOfBuilding;}
inline bool Hand::hasNoHarvest() {return (*numOfHarvest == 0);}
inline bool Hand::hasNoBuilding() { return (*numOfBuilding == 0);}

inline HarvestTile* Hand::getHarvestTile(int index) {return harvestHold[0][index];}
inline BuildingTile* Hand::getBuildingTile(int index) { return buildingHold[0][index]; }

