#include <iostream>
#include <string>
#include <vector>
#include <ctime>

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
using cimg_library::CImgDisplay;

static Game* game;
static int numberOfPlayers;

CImgDisplay main_disp;
int main_disp_x;
int main_disp_y;
MapDrawer* drawer;

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
}



void testGame() {

	// CIMG Window Draw Loop
	
		for (int i = 0; !game->getGBMap()->GameOver(); i = ++i%numberOfPlayers) {
			cout << "i is ... " << i << endl;
			cout << "START OF " << *game->getPlayer(i)->getName() << "'s turn!" << endl;

			// Set current player to index i
			game->setCurrentPlayer(game->getPlayer(i));

			UpdateDisplay();

			// Have the player place a shipment tile.
			// TODO: Make this optional! 
			game->getPlayer(i)->PlaceShipmentTile(game->getGBMap());

			UpdateDisplay();

			game->getPlayer(i)->PlaceHarvestTile(game->getGBMap());

			UpdateDisplay();

			game->getPlayer(i)->PlaceBuildingTile(game->getPlayer(i)->getVGMap());

			cout << "Number of points from VGMap: " << game->getPlayer(0)->getVGMap()->calculatePoints() << endl;

			cout << "Shipment Tile flipped!" << endl; 
			game->getPlayer(i)->UncoverShipment(game->getGBMap());

			cout << "Drawing a new Harvest tile card!" << endl;
			game->playerDraw(i);

			UpdateDisplay();

			cout << "END OF " << *game->getPlayer(i)->getName() << "'s turn!" << endl;
			system("Pause");

			//main_disp.wait();
		}

	cout << "*** THE GAME HAS ENDED!!! ***" << endl;

}

int main() {
	srand(time(nullptr));

	initialize();
	testGame();

	return 0;
}
