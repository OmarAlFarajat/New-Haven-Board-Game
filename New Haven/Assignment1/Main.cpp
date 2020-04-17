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

void initialize();
void PlayHarvest(int);
void BuildVillage(int);
void ShareWealth(int);
void DrawBuildings(int);
void EndTurn(int);
//void DrawBuildingsHelper(int, int);

int main() {

	srand(time(nullptr));

	initialize();
	// A3. Creating the observers and attaching them to the subjects (via constructors). 
	GameObserver GameObserver(game);
	GBMapObserver GBMapObserver(game->getGBMap());
	// One VGMap observer per player 
	vector<VGMapObserver*> VGMapObservers;
	for (int i = 0; i < numberOfPlayers; i++) {
		VGMapObservers.push_back(new VGMapObserver(game->getPlayer(i)->getVGMap()));
	}

	// Keeps track of the game turn
	int turn_counter = 1;

	// MAIN GAME LOOP
	for (int player_index = 0; !game->getGBMap()->GameOver(); player_index = ++player_index % numberOfPlayers) {

		shipmentPlayed = false; 

		// A3. GameObserver will be notified by using setCurrentPlayer. 
		game->setCurrentPlayer(game->getPlayer(player_index));

		cout << "\n*****************************" << endl; 
		cout << "*** START OF " << *game->getPlayer(player_index)->getName() << "'s TURN! ***" << endl;
		cout << "Game turn: " << turn_counter << endl;
		turn_counter++;

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
		cout << "Player " << *game->getPlayer(i)->getName() << " : " << game->getPlayer(i)->getScore() << endl;
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
			cout << "\n >>>> The winner is " << *game->getPlayer(i)->getName() << " with " << bestScore << endl;
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
	std::map<ResourceType, int>* resources = game->getGBMap()->getResourceTracker();

	// TODO: Redo this count more efficiently...
	int zeroCount = 0;
	if (resources[0][ResourceType::SHEEP] == 0)
		zeroCount++;
	if (resources[0][ResourceType::STONE] == 0)
		zeroCount++;
	if (resources[0][ResourceType::WHEAT] == 0)
		zeroCount++;
	if (resources[0][ResourceType::TIMBER] == 0)
		zeroCount++;

	//////
	// TODO: Draw one building for every resource marker at 0. Must first draw from GBMap's Available Buildings. 
	/////

	///	TEMPORARY: For now, player simply draws 1 Building from the deck at the end so long as their hand has less than 12. 
	///	There is no interaction with the Buildings on the gameboard for now (will be fixed by A3). 

	cout << ">>> Drawing a new Building card from the deck!" << endl;
	if (game->getPlayer(0)->getHand()->getRemainBuilding() < 12)
		game->playerDrawBuilding(player_index);

	////	WORKING CODE, commented out. Simple "stand-in" behaviour above. 

	//validInput = false;
	//switch (zeroCount) {
	//case 0:
	//	break;
	//case 1:
	//	cout << ">>> You must draw 1 Building from the gameboard!" << endl;
	//	//
	//	break;
	//case 2:
	//	DrawBuildingsHelper(zeroCount, player_index);
	//	break;
	//case 3:
	//	DrawBuildingsHelper(zeroCount, player_index);
	//	break;
	//case 4:
	//	DrawBuildingsHelper(zeroCount, player_index);
	//	break;
	//}
}

//void DrawBuildingsHelper(int zeroCount, int player_index) {
//	int numDrawFromGB = 0;
//	while (!validInput) {
//		cout << ">>> You must draw " << zeroCount << " Buildings, with at least 1 from the gameboard!" << endl;
//		cout << "\t>>> Besides the mandatory Building, how many do you want to draw from the gameboard?" << endl;
//		cin >> numDrawFromGB;
//		if (numDrawFromGB < 0 || numDrawFromGB > zeroCount - 1) {
//			cout << ">>> Invalid input, try again..." << endl;
//			validInput = false;
//			continue;
//		}
//
//		validInput = true;
//	}
//
//	for (int i = 0; i < numDrawFromGB; i++) {
//		int choice = 0;
//		while (!validInput) {
//			cout << ">>> Select the Building ID from the gameboard you'd like to draw (" << i << "/" << numDrawFromGB << "): " << endl;
//			cin >> choice;
//			if (!(game->getGBMap()->getBuildingsAvailable() + choice)) {
//				cout << ">>> Invalid input, try again..." << endl;
//				validInput = false;
//				continue;
//			}
//			
//			validInput = true;
//
//		}
//
//
//	}
//}

void EndTurn(int player_index) {

	cout << "Resetting Resource Tracker..." << endl;
	
	std::map<ResourceType, int> resetResources = { {ResourceType::SHEEP, 0}, { ResourceType::STONE,0 }, { ResourceType::TIMBER,0 }, { ResourceType::WHEAT,0 } };

	game->getGBMap()->setResourceTracker(&resetResources);

	if (shipmentPlayed) {
		cout << "Shipment Tile flipped!" << endl;
		game->getPlayer(player_index)->UncoverShipment(game->getGBMap());
		UpdateDisplay();
	}

	cout << ">>> Drawing a new Harvest card from the deck!" << endl;
	if (game->getPlayer(0)->getHand()->getRemainHarvest() < 2)
		game->playerDrawHarvest(player_index);
	UpdateDisplay();
}
