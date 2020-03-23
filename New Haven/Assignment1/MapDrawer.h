#pragma once
#include "GBMap.h"
#include "CImg.h"
#include "Player.h"

using namespace cimg_library;
using std::unique_ptr;

class MapDrawer {
	//Global variables
	const unsigned char black[3] = { 0,0,0 };
	const unsigned char vagueBrown[3] = { 224,192,128 };

	unique_ptr<CImg<unsigned char>> MAP_TILE;
	unique_ptr<CImg<unsigned char>> DISABLED_TILE;

	unique_ptr<CImg<unsigned char>> RESOURCE_TRACKER;
	unique_ptr<CImg<unsigned char>> AVAILABLE_BUILDINGS;

	unique_ptr<CImg<unsigned char>> NONE;

	unique_ptr<CImg<unsigned char>> SHEEP;
	unique_ptr<CImg<unsigned char>> STONE;
	unique_ptr<CImg<unsigned char>> WHEAT;
	unique_ptr<CImg<unsigned char>> TIMBER;

	unique_ptr<CImg<unsigned char>> GREEN_TRACKER;
	unique_ptr<CImg<unsigned char>> GREY_TRACKER;
	unique_ptr<CImg<unsigned char>> YELLOW_TRACKER;
	unique_ptr<CImg<unsigned char>> RED_TRACKER;

	unique_ptr<CImg<unsigned char>> GREEN_BUILDING;
	unique_ptr<CImg<unsigned char>> GREY_BUILDING;
	unique_ptr<CImg<unsigned char>> YELLOW_BUILDING;
	unique_ptr<CImg<unsigned char>> RED_BUILDING;

	unique_ptr<CImg<unsigned char>> GREEN_BUILDING_DOWN;
	unique_ptr<CImg<unsigned char>> GREY_BUILDING_DOWN;
	unique_ptr<CImg<unsigned char>> YELLOW_BUILDING_DOWN;
	unique_ptr<CImg<unsigned char>> RED_BUILDING_DOWN;

public:
	MapDrawer(); // setting up global variables
	CImg<unsigned char> ResourceToBMP(ResourceType type);
	CImg<unsigned char> BuildingToBMP(ResourceType type);
	CImg<unsigned char> BuildingDownToBMP(ResourceType type);

	CImg<unsigned char> drawColumnIndicators(GBMap& const gb_map);
	CImg<unsigned char> drawGBMap(GBMap& const gb_map);
	CImg<unsigned char> drawVGMap(Player& const player);
	void drawHarvestOnHand(Player& const player, std::shared_ptr<CImg<unsigned char>> HAND);
	void drawBuildingsOnHand(Player& const player, std::shared_ptr<CImg<unsigned char>> HAND);
	CImg<unsigned char> drawHand(Player& const player);
	void drawResourceTracker(GBMap& const gb_map);

	CImg<unsigned char> drawGame(GBMap& gb_map, Player& player);
};
