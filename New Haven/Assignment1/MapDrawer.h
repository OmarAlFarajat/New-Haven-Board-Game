#pragma once
#include "GBMap.h"
#include "CImg.h"
#include "Player.h"
#include "Game.h"

using namespace cimg_library;
using std::unique_ptr;

class MapDrawer {
	Game* game;
	const unsigned char black[3] = { 0,0,0 };
	const unsigned char vagueBrown[3] = { 224,192,128 };

	unique_ptr<CImg<unsigned char>> MAP_TILE;
	unique_ptr<CImg<unsigned char>> DISABLED_TILE;

	unique_ptr<CImg<unsigned char>> RESOURCE_TRACKER;
	unique_ptr<CImg<unsigned char>> AVAILABLE_BUILDINGS;

	unique_ptr<CImg<unsigned char>> GAME_TITLE;

	unique_ptr<CImg<unsigned char>> NONE;

	unique_ptr<CImg<unsigned char>> SHIPMENTBACK;
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
	MapDrawer(Game* const game); // setting up global variables
	CImg<unsigned char> ResourceToBMP(ResourceType type);
	CImg<unsigned char> BuildingToBMP(ResourceType type);
	CImg<unsigned char> BuildingDownToBMP(ResourceType type);

	CImg<unsigned char> drawColumnIndicators();
	CImg<unsigned char> drawGBMap();
	CImg<unsigned char> drawVGMap();
	void drawHarvestOnHand(std::shared_ptr<CImg<unsigned char>> HAND);
	void drawBuildingsOnHand(std::shared_ptr<CImg<unsigned char>> HAND);
	CImg<unsigned char> drawHand();
	void drawResourceTracker();

	CImg<unsigned char> Update();
};
