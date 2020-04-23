#include "Hand.h"
//#include "MapDrawer.h"
#include "CImg.h"
#include "DrawDisplay.h"

using cimg_library::CImgDisplay;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::exception;

Hand::Hand()
{
	numOfHarvest = new int(0);
	numOfBuilding = new int(0);
	harvestHold = new vector<HarvestTile*>(0);
	buildingHold = new vector<BuildingTile*>(0);
	SHIPMENT_TILE = new HarvestTile();
	containSHIPMENT = new bool(false);
	SHIPMENTlocation = new vector<int*>();
}

Hand::~Hand()
{
	delete numOfHarvest;
	numOfHarvest = nullptr;
	delete numOfBuilding;
	numOfBuilding = nullptr;
	delete harvestHold;
	harvestHold = nullptr;
	delete buildingHold;
	buildingHold = nullptr;
	//delete SHIPMENT_TILE;
	SHIPMENT_TILE = nullptr;
	delete containSHIPMENT;
	containSHIPMENT = nullptr;
}

void Hand::printOccupiedPositionMessage() {
	cout << ">>> INVALID CHOICE. The position is either occupied or invalid. Please try again." << endl;
	//cout << "\n------------------------------------------" << endl;
	//cout << "The position is either occupied or invalid" << endl;
	//cout << "Please try again." << endl;
	//cout << "------------------------------------------\n" << endl;
}

void Hand::setShipmentLocation(int row, int col) {
	SHIPMENTlocation->push_back(new int(row));
	SHIPMENTlocation->push_back(new int(col));
}

void Hand::showHarvests() {
	// Showing Harvest cards on Hand, including SHIPMENT TILE (if having)
	cout << "\nShowing Harvest Tiles on Hand" << endl;
	for (int i = 0; i < this->getRemainHarvest(); ++i) {
		cout << "Harvest Tile no." << i << endl;
		cout << *harvestHold[0][i] << endl;
	}

	if (hasSHIPMENT_TILE()) {
		cout << *getSHIPMENT_TILE() << endl;
	}
}

void Hand::showBuildings() {
	//Showing Buildings cards on Hand
	cout << "Showing Buildings on Hand" << endl;
	for (int i = 0; i < this->getRemainBuilding(); ++i) {
		cout << "Building Tile no." << i << endl;
		cout << *buildingHold[0][i] << endl;
	}
}

void Hand::showHand()
{
	cout << "Showing cards on hand:" << endl;
	Hand::showHarvests();
	Hand::showBuildings();
}

void Hand::addSHIPMENT(HarvestTile* shipment)
{
	SHIPMENT_TILE = shipment;
	SHIPMENT_TILE->setShipmentStatus(true);
	*containSHIPMENT = true;
}

void Hand::addHarvestTile(HarvestTile* ht)
{
	harvestHold->push_back(ht);
	*numOfHarvest = *numOfHarvest + 1;
}

void Hand::addBuildingTile(BuildingTile* bt)
{
	buildingHold->push_back(bt);
	*numOfBuilding = *numOfBuilding + 1;
}

/*
2 functions getNodeID and getNodeID_VG
were used to get the corresponding node ID on the map
of the provided location and the map itself
*/

int Hand::getNodeID_GB(GBMap* gb_map, int row, int col)
{
	int length = gb_map->getTileGraph()->getLength();
	return (row * length + col);
}

int Hand::getNodeID_VG(VGMap* vg_map, int row, int col)
{
	int length = vg_map->getBuildingGraph()->getLength();
	return (row * length + col);
}

/*
Function exchange will calculate the generated resources from a player's move
Then, set the Resource Tracker (located on the GBMap).
Finally, display the generated resources.
*/
void Hand::exchange(GBMap* gb_map, TileNode* location)
{
	std::map<ResourceType, int> generatedResources = { {ResourceType::SHEEP,0},{ResourceType::STONE,0},{ResourceType::TIMBER,0},{ResourceType::WHEAT,0} };
	gb_map->calcResourceAdjacencies(location, generatedResources);
	gb_map->setResourceTracker(&generatedResources);
	//gb_map->displayResourceTracker();
}

vector<int> Hand::askHarvestLocation(GBMap* const gb_map)
{
	vector<int> location;
	//Ask for position on the map to place tile
	int row, col;
	cout << "\t>>> Enter the row you want to play it on:" << endl;
	cin >> row;
	if (row < 0 || row >= gb_map->getTileGraph()->getHeight()) {
		throw exception();
	}

	cout << "\t>>> Enter the column you want to play it on:" << endl;
	cin >> col;
	if (col < 0 || col >= gb_map->getTileGraph()->getLength()) {
		throw exception();
	}

	location.push_back(row);
	location.push_back(col);
	return location;

}

ResourceType Hand::askTypeForShipment()
{
	string menu = "\t1. TIMBER\n\t2. STONE\n\t3. WHEAT\n\t4. SHEEP";
	int choice;
	while (true) {
		cout << ">>> Select the type of Resource for your Shipment Tile" << endl;
		cout << menu << endl;
		try {
			cin >> choice;
			if (choice < 0 || choice > 4) {
				throw exception();
			}
			break;
		}
		catch (const exception & e) {
			cout << "Invalid input. Please try again" << endl;
		}
	}

	switch (choice) {
		case 1: return ResourceType::TIMBER;
		case 2: return ResourceType::STONE;
		case 3:	return ResourceType::WHEAT;
		case 4:	return ResourceType::SHEEP;
		default: return ResourceType::NONE;
	}

}

/*
Return false if operation fails.
*/
bool Hand::playSHIPMENT(GBMap* gb_map)
{
	//Safe guard
	if (!hasSHIPMENT_TILE()) {
		cout << "\n You do not have any SHIPMENT TILE left\n" << endl;
		return false;
	}

	SHIPMENT_TILE->makeShipmentOf(askTypeForShipment());
	
	int row, col;
	try {
		vector<int> coordination= askHarvestLocation(gb_map);
		row = coordination[0];
		col = coordination[1];
	}
	catch (const exception & e) {
		cout << "Invalid position" << endl;
		return false;
	}
	
	int nodeID = this->getNodeID_GB(gb_map, row, col);
	TileNode* location = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(nodeID));
	if (gb_map->isValid(location)) {
		gb_map->placeHarvestTile(SHIPMENT_TILE, location);
		//cout << "\nPLACED SHIPMENT TILE ON THE GAMEBOARD SUCCESSFULLY\n" << endl;
		setShipmentLocation(row, col);
		exchange(gb_map, location);
		SHIPMENT_TILE->setShipmentStatus(false);
		*containSHIPMENT = false;
	}
	else {
		printOccupiedPositionMessage();
		return false;
	}

	return true;
}

void Hand::uncoverShipment(GBMap* gb_map)
{
	int nodeID = this->getNodeID_GB(gb_map, *SHIPMENTlocation[0][0], *SHIPMENTlocation[0][1]);
	auto location = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(nodeID));
	gb_map->placeHarvestTile(SHIPMENT_TILE, location);
	/*
	cout << "DEBUG: Uncovering the shipment tile and re calculate the resources gathered" << endl;
	cout << *SHIPMENT_TILE << endl;
	exchange(gb_map, location); 
	*/
}

/*
A function asking and validating user's prefered orientation of the Harvest Tile they are playing
*/
bool Hand::requestRotate(HarvestTile* target)
{

	char input;
	char back = 'b';
	char end = 'e';
	char rotate = 'r';

	while (true) {
		//cout << "\n---------------" << endl;
		//cout << "Your Harvest Tile:" << endl;
		//cout << *target << endl;
		//cout << "---------------" << endl;
		
		cout << ">>> Chosen Harvest Tile options: " << endl;
		cout << "\t+ Place it: e" << endl;
		cout << "\t+ Rotate clockwise: r" << endl;
		cout << "\t+ Choose another: b" << endl;
		vector<ResourceType>* container = target->getContainerPointer();

		try {
			cin >> input;

			if (input == back) {
				target->setIsSelected(false);
				return false;
			}

			if (input == end) {
				//cout << "------------------------------------------" << endl;
				//cout << "Placing Tile on the gameboard" << endl;
				//cout << "------------------------------------------" << endl;
				return true;

			}

			if (input == rotate) {
				// Mimic a deque for rotating clockwise 
				//cout << "Rotating ..." << endl;
				ResourceType temp = container[0][3];
				container[0].insert(container[0].begin(), temp);
				container[0].erase(container[0].end() - 1);
				UpdateDisplay();
				continue;
			}

			throw exception();
		}
		catch (const exception & e) {
			cout << "Invalid input. Please try again" << endl;
			continue;
		}

	}

}

int Hand::askHarvestChoice()
{
	//Ask for choice of Harvest Tile on hand
	int choice = -1;
	//cout << "\nCurrently, you are having " << getRemainHarvest() << " Harvest Tiles on your hand" << endl;
	cout << ">>> Enter the ID of the Harvest Tile you want to play: " << endl;
	try {
		cin >> choice;
		if (choice < 0 || choice >= this->getRemainHarvest()) {
			throw exception();
		}
		return choice;
	}
	catch (const exception & e) {
		cout << "Invalid choice. Please try again." << endl;
		return -1;
	}

}



/*
Function to start playing Harvest Tile and placing the tile on the board if it is valid
*/
int Hand::playHarvest(GBMap* gb_map) {
	//cout << "\n----PLAYING HARVEST TILE----" << endl;
	while (true) {
		if (hasNoHarvest()) {
			cout << "There is no Harvest Tile on hand to play" << endl;
			return 1;
		}

		//showHand();
		UpdateDisplay();

		//Ask fow which Harvest tile to be played
		int choice = askHarvestChoice();
		if (choice == -1) 
			continue;
		HarvestTile* target = getHarvestTile(choice);
		target->setIsSelected(true);
		UpdateDisplay();

		//Ask for position on the map to place tile
		int row, col;
		try {
			//location stores the coordinate of requested position to place the tile
			vector<int> location = askHarvestLocation(gb_map);
			row = location[0];
			col = location[1];
		}
		catch (const exception & e) {
			cout << "Invalid position input. Please try again" << endl;
			target->setIsSelected(false);
			continue;
		}

		/* Check if the position is enabled and not occupied
		=> process to rotate the Tile as requested
		=> Place Tile on the map and calculate resources by exchange
		*/
		int nodeID = this->getNodeID_GB(gb_map, row, col);
		TileNode* location = static_cast<TileNode*>(gb_map->getTileGraph()->getNode(nodeID));
		if (gb_map->isValid(location)) {
			if (requestRotate(target)) {
				// User satisfies with their choice of rotation, process to place HarvestTile
				gb_map->placeHarvestTile(target, location);
				//cout << "\nPLACED TILE ON THE GAMEBOARD SUCCESSFULLY\n" << endl;
				exchange(gb_map, location);
				harvestHold->erase(harvestHold[0].begin() + choice); //Remove the tile from hand after placement
				*numOfHarvest = *numOfHarvest - 1;
				break;
			}

		}
		else {
			printOccupiedPositionMessage();
			target->setIsSelected(false);
			continue;
		}
	}

	return 0;
}

/*
A function to ask and validate player's request on flipping the Building Tile or not
*/
bool Hand::requestFlip(BuildingTile* target) {
    //cout << "\n---Start flipping---" << endl;

    char input;
    char back = 'b';
    char end = 'e';
    char flip = 'f';
    char question = '?';

	 string faceStatus;
    while (true) {
		faceStatus = target->isFaceUp() ? "Up" : "Down";
		cout << ">>> Chosen Building is " << faceStatus << ". Options:" << endl;
		cout << "\t+ Place it: e" << endl;
        cout << "\t+ Flip the Tile: f" << endl;
        cout << "\t+ Choose another Tile: b" << endl;
        cout << "\t+ Help with flipping: ?" << endl;

        try {
            cin >> input;

            if (input == back) {
                return false;
            }

            if (input == end) {
                //cout << "------------------------------------------" << endl;
                //cout << "Validating the request" << endl;
                //cout << "------------------------------------------" << endl;
                return true;

            }

            if(input == question) {
                cout << "----OVERVIEW----" << endl;
                cout << "\nBuildings may only be played face up if the number on the\n"
                             "\t space matches the number showing on the Building." << endl;
                cout << "\nBuildings may be played face down onto any number space,\n"
                             "\t regardless of the number on the Building." << endl;
                cout << "\nThe value of each row and column is the number\n"
                             "of Colonists shown at the right or bottom. BUT! The value of a row or column is doubled if every\n"
                             "Building played on that row or column is face up!" << endl;
                continue;
            }

            if(input == flip) {
                //cout << "\nFlipping the tile" << endl;
                target->setFaceUp(!target->isFaceUp());
                //if(target->isFaceUp()) {
                //    cout << "The Building Tile is faced up." << endl;
                //    cout << "You CAN earn double points if you complete the whole column or row corresponding to the position of this card" << endl;
                //} else {
                //    cout << "The Building Tile is faced down." << endl;
                //    cout << "You CANNOT earn double points if you complete the whole column or row corresponding to the position of this card" << endl;
                //}
                continue;
            }

            throw exception();
        }
        catch (const exception & e) {
            cout << "Invalid input. Please try again" << endl;
            continue;
        }

    }

}

int Hand::askBuildingChoice()
{
	//Ask for choice of Building Tile from hand
	int choice = -1;
	//cout << "\nCurrently, you have " << getRemainBuilding() << " Building tiles in your hand" << endl;
	cout << ">>> Enter the ID of Building Tile you want to play:" << endl;
	try {
		cin >> choice;
		if (choice < 0 || choice >= this->getRemainBuilding()) {
			throw exception();
		}
		return choice;
	} 
	catch (const exception & e) {
		cout << "Invalid choice. Please try again." << endl;
		return -1;
	}

}

vector<int> Hand::askBuildingLocation(VGMap* const vg_map)
{
	//Ask for position on the map to place tile
	int row, col;
	vector<int> location;
	cout << "\t>>> Enter the row you want to play it on:" << endl;
	cin >> row;
	if (row < 0 || row >= vg_map->getBuildingGraph()->getHeight()) {
		throw exception();
	}

	cout << "\t>>> Enter the column you want to play it on:" << endl;
	cin >> col;
	if (col < 0 || col >= vg_map->getBuildingGraph()->getLength()) {
		throw exception();
	}

	location.push_back(row);
	location.push_back(col);
	return location;

}

/*
Function to start playing Building Tile and placing the tile on the village board if it is valid
(build village)
*/
void Hand::playBuilding(VGMap* vg_map, GBMap* const gb_map) {
	//cout << "\n----PLAYING BUILDING TILE----" << endl;
	while (true) {
		if (hasNoBuilding()) 
			cout << "There is no Building Tile on hand to play" << endl;
		
		//showHand();

		int choice = askBuildingChoice();
		BuildingTile* target = getBuildingTile(choice);

		// Validate if player has enough resources
		if (!gb_map->isValidExpense(target->getType(), target->getValue())) {
			cout << "INSUFFICIENT RESOURCES: You do not have enough resources to construct this building" << endl;
			break;
		}

		int row, col;
		try {
			vector<int> location = askBuildingLocation(vg_map);
			row = location[0];
			col = location[1];
		} 
		catch (const exception & e) {
			cout << "Invalid position input. Please try again" << endl;
			continue;
		}

		/* Check if the position is enabled and not occupied
		=> process to flip the tile as requested
		=> Place Tile on the map.
		*/
		int nodeID = this->getNodeID_VG(vg_map, row, col);
		BuildingTile* location = static_cast<BuildingTile*>(vg_map->getBuildingGraph()->getNode(nodeID));
		if (requestFlip(target)) {
		    if(vg_map->isValid(target, location)) {
                vg_map->placeBuildingTile(target, location);
				        gb_map->spendResource(target->getType(), target->getValue());
                //cout << "\nPLACED TILE ON THE VGBOARD SUCCESSFULLY\n" << endl;
                buildingHold->erase(buildingHold[0].begin() + choice); //Remove the tile from hand after placement
                *numOfBuilding = *numOfBuilding - 1;
                break;
		    } else {
				printOccupiedPositionMessage();
				break;
            }
		}

	}
}

