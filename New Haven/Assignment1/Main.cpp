#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <queue>

#include "GBMap.h"
#include "Resources.h"
#include "Harvest.h"
#include "Building.h"
#include "Hand.h"
#include "Player.h"
#include "TileNode.h"
#include "VGMap.h"
#include "VGMapLoader.h"
#include "MapDrawer.h"
#include "Game.h"
#include "CImg.h"
#include "DrawDisplay.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using cimg_library::CImgDisplay;

static Game* game;
static int numberOfPlayers;
static int validInput; 
static char answer;
static bool shipmentPlayed; 
void scoreBoard();

void UpdateDisplay();
CImgDisplay main_disp;
int main_disp_x;
int main_disp_y;
MapDrawer* drawer;

//void testGame();

void initialize();
void PlayHarvest(int);
//void DetermineResources(int);
void BuildVillage(int);
void ShareWealth(int);
void DrawBuildings(int);
void EndTurn(int);

int main() {

	srand(time(nullptr));

	initialize();

	int turn_counter = 1;

	for (int player_index = 0; !game->getGBMap()->GameOver(); player_index = ++player_index % numberOfPlayers) {

		shipmentPlayed = false; 

		cout << "\n*****************************" << endl; 
		cout << "*** START OF " << *game->getPlayer(player_index)->getName() << "'s TURN! ***" << endl;
		cout << "Game turn: " << turn_counter << endl;
		turn_counter++;
		game->setCurrentPlayer(game->getPlayer(player_index));
		UpdateDisplay();

		// 1: Play a Harvest Tile
		PlayHarvest(player_index);
		// 2: Determine Resources Gathered (Is done implicitly when a harvest tile is placed)
		// 3: Build Your Village
		BuildVillage(player_index);
		// 4: Share the Wealth
		if (game->getGBMap()->hasWealthToShare())
			ShareWealth(player_index);
		// 5: Draw Buildings
		DrawBuildings(player_index);
		// 6: End of Turn
		EndTurn(player_index);

		cout << "*** END OF " << *game->getPlayer(player_index)->getName() << "'s turn! ***" << endl;
		cout << "*****************************" << endl;
		
	}
	scoreBoard();
	return 0;
}

//TODO: Implement to find the winner with more filters
void scoreBoard() {
	cout << "*******************************" << endl;
	cout << "            GAME ENDS           " << endl;
	cout << "***********SCORE BOARD***********" << endl;

	std::priority_queue<int> scoreBoard;
	for (int i = 0; i < numberOfPlayers; ++i) {
		int gainedScore = game->getPlayer(i)->getVGMap()->calculatePoints();
		game->getPlayer(i)->setScore(gainedScore);
		cout << "Player " << game->getPlayer(i)->getName() << " : " << game->getPlayer(i)->getScore() << endl;
		scoreBoard.push(gainedScore);
	}

	int bestScore = 0;
	for (int i = 0; i < numberOfPlayers; ++i) {
		int examining = game->getPlayer(i)->getScore();
		if (examining > bestScore) {
			bestScore = examining;
		}
	}

	for (int i = 0; i < numberOfPlayers; ++i) {
		int examining = game->getPlayer(i)->getScore();
		if (examining == bestScore) {
			cout << " CONGRATULATION " << endl;
			cout << "\n >>>> The winner is " << game->getPlayer(i)->getName() << " with " << bestScore << endl;
		}
	}

}


void UpdateDisplay() {
	main_disp = CImgDisplay(drawer->Update(), "New Haven");
	main_disp.move(main_disp_x, main_disp_y);
}

void initialize() {
	// CIMG Main Display
	main_disp = CImgDisplay();
	main_disp_x = 0;
	main_disp_y = 25;

	// User prompted for number of players
	cout << "Please enter the number of players: " << endl;
	cin >> numberOfPlayers;
	game = new Game(numberOfPlayers);
	drawer = new MapDrawer(game);
	validInput = false;
}

void PlayHarvest(int player_index) {

	if (game->getPlayer(player_index)->getHand()->hasSHIPMENT_TILE()) {

		validInput = false;
		while (!validInput) {
		cout << ">>> Would you like to place your Shipment tile instead of your Harvest tile? (y/n)" << endl;
		cin >> answer;
			switch (answer) {
			case 'y':
				if (game->getPlayer(player_index)->PlaceShipmentTile(game->getGBMap())) {
					validInput = true;
					shipmentPlayed = true;
					UpdateDisplay();
				}
				else {
					validInput = false;
					shipmentPlayed = false;
				}
				break;
			case 'n':
				game->getPlayer(player_index)->PlaceHarvestTile(game->getGBMap());
				UpdateDisplay();
				validInput = true;
				shipmentPlayed = false;
				break;
			default:
				cout << "INVALID INPUT. Try again..." << endl;
				validInput = false;
				shipmentPlayed = false;
			}
		} 
	}
}
void BuildVillage(int player_index) {

	if (!game->getPlayer(player_index)->getHand()->hasNoHarvest()) {
		bool wantsToBuild = false;
		validInput = false;

		while (!validInput){
			cout << ">>> Would you like to build any buildings? (y/n)" << endl;
			cin >> answer;
			switch (answer) {
			case 'y':
				wantsToBuild = true;
				validInput = true;
				break;
			case 'n':
				wantsToBuild = false;
				validInput = true;
				break;
			default:
				cout << "INVALID INPUT. Try again..." << endl;
				validInput = false;
			}
		} 

		while (wantsToBuild) {
			game->getPlayer(player_index)->PlaceBuildingTile(game->getPlayer(player_index)->getVGMap(), game->getGBMap());
			UpdateDisplay();

			validInput = false;
			while (!validInput && !game->getPlayer(player_index)->getHand()->hasNoHarvest()) {
				cout << ">>> Would you like to build another building? (y/n)" << endl;
				cin >> answer;

				switch (answer) {
				case 'y':
					wantsToBuild = true;
					validInput = true;
					break;
				case 'n':
					wantsToBuild = false;
					validInput = true;
					break;
				default:
					cout << "INVALID INPUT." << endl;
					validInput = false;
				}
			} 
		}
	}
}

void ShareWealth(int player_index) {
	cout << ">>> There are some unused resources. Start sharing wealth turn" << endl;
	//cout << ">>> Number of points from VGMap: " << game->getPlayer(0)->getVGMap()->calculatePoints() << endl;
	int new_player_index = player_index;
	for (int i = ++new_player_index % numberOfPlayers; i == new_player_index; i = ++i % numberOfPlayers) {
		cout << "*** START " << *game->getPlayer(new_player_index)->getName() << "'s SHARE WEALTH TURN! ***" << endl;
		game->setCurrentPlayer(game->getPlayer(i));
		UpdateDisplay();
		BuildVillage(i);
	}
	game->setCurrentPlayer(game->getPlayer(player_index)); // back on track
	cout << "*** BACK TO " << *game->getPlayer(player_index)->getName() << "'s TURN! ***" << endl;
}

void DrawBuildings(int player_index) {
	
	//////
	// TODO: Draw one building for every resource marker at 0. Must first draw from GBMap's Available Buildings. 
	/////

	cout << ">>> Drawing a new Harvest tile card!" << endl;
	if(game->getPlayer(0)->getHand()->getRemainHarvest() < 2)
		game->playerDraw(player_index);
	UpdateDisplay();
}

void EndTurn(int player_index) {

	cout << "Resetting Resource Tracker..." << endl;
	
	std::map<ResourceType, int> resetResources = { {ResourceType::SHEEP, 0}, { ResourceType::STONE,0 }, { ResourceType::TIMBER,0 }, { ResourceType::WHEAT,0 } };

	game->getGBMap()->setResourceTracker(&resetResources);

	if (shipmentPlayed) {
		cout << "Shipment Tile flipped!" << endl;
		game->getPlayer(player_index)->UncoverShipment(game->getGBMap());
		UpdateDisplay();
	}
}
