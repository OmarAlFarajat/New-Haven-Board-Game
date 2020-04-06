#include <iostream>
#include "Game.h"
#include "VGMap.h"
#include "Player.h"
#include "GBMapLoader.h"

using std::cout;
using std::cin;
using std::endl;
using std::endl;
using std::string;

Game::Game(int number_of_players)
{
	Players = new vector<Player*>();
	gb_map = new GBMap();
	harvestDeck = new HarvestDeck();
	buildingDeck = new BuildingDeck();
	currentPlayer = nullptr;

	string inputName;
	for (int i = 0; i < number_of_players; i++) {
		cout << "Please input the name of player #" << i << ": " << endl;
		cin >> inputName;
		Players->push_back(new Player(inputName, i));
	}

	string mapFileName;
	// Switch statement assigns a string to fileName
	switch (number_of_players) {
	case 2:
		//mapFileName = "./Maps/GBA_2Players.gbmap";
		//mapFileName = "./Maps/GBA_2Players_resourceTest.gbmap";
		//mapFileName = "./Maps/GBA_2Players_invalid.gbmap";
		//mapFileName = "./Maps/GBA_2Players_testWinner.gbmap"; failing
		mapFileName = "./Maps/GBA_2Players_fullBoardSize.gbmap";
		break;
	case 3:
		//mapFileName = "./Maps/GBA_3Players.gbmap";
		mapFileName = "./Maps/GBA_3Players_fullBoardSize.gbmap";
		break;
	case 4:
		mapFileName = "./Maps/GBA_4Players.gbmap";
		break;
	default:
		cout << "* YOU ENTERED AN INVALID NUMBER OF PLAYERS. GOODBYE! *" << endl;
	}

	loadGBMap(mapFileName, *this->gb_map);

	cout << ">>> Number of cards in Harvest deck before setup: " << harvestDeck[0].getNumOfRemain() << endl;
	cout << ">>> Number of cards in Building deck before setup: " << buildingDeck[0].getNumOfRemain() << endl;

	for (int i = 0; i < Players[0].size(); i++) {
		int drawHarvest = 2;
		//std::cout << "Drawing " << drawHarvest << " Harvest Tiles" << std::endl;
		for (int j = 0; j < drawHarvest; ++j) {
			Players[0][i]->DrawHarvestTile(harvestDeck);
		}

		int drawBuilding = 6;
		//std::cout << "Drawing " << drawBuilding << " Building Tiles" << std::endl;
		for (int j = 0; j < drawBuilding; ++j) {
			Players[0][i]->DrawBuilding(buildingDeck);
		}

		Players[0][i]->DrawShipment(harvestDeck);
	}

	FillAvailableBuildings();

	cout << ">>> Number of cards in Harvest deck after setup: " << harvestDeck[0].getNumOfRemain() << endl;
	cout << ">>> Number of cards in Building deck after setup: " << buildingDeck[0].getNumOfRemain() << endl;
}

Game::~Game()
{
	delete Players;
	Players = nullptr;

	delete gb_map;
	gb_map = nullptr;

}

void Game::playerDraw(int player_index)
{
	Players[0][player_index]->DrawHarvestTile(harvestDeck);
	cout << ">>> Harvests remaining: " << harvestDeck[0].getNumOfRemain() << endl; 
	cout << ">>> Buildings remaining: " << buildingDeck[0].getNumOfRemain() << endl;

}

void Game::FillAvailableBuildings() {

	int number_building_spots = 5; 
	for (int i = 0; i < number_building_spots; i++)
		if (!gb_map->buildingsAvailable[i]) {
			gb_map->buildingsAvailable[i] = new BuildingTile();
			gb_map->buildingsAvailable[i] = gb_map->DrawBuilding(buildingDeck);
			cout << *gb_map->buildingsAvailable[i]; 
		}
}