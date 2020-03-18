#include <string> 
#include "MapDrawer.h"
using std::cout;
using std::endl; 
using std::vector;
using std::to_string;

CImg<unsigned char> ResourceToBMP(ResourceType type) {
    CImg<unsigned char> SHEEP("./Images/Sheep.BMP");
    CImg<unsigned char> STONE("./Images/Stone.BMP");
    CImg<unsigned char> TIMBER("./Images/Timber.BMP");
    CImg<unsigned char> WHEAT("./Images/Wheat.BMP");
    CImg<unsigned char> NONE("./Images/None.BMP");
    switch (type) {
    case ResourceType::NONE:
        return NONE;
    case ResourceType::SHEEP:
        return SHEEP;
    case ResourceType::STONE:
        return STONE;
    case ResourceType::WHEAT:
        return WHEAT;
    case ResourceType::TIMBER:
        return TIMBER;
    }
}

CImg<unsigned char> BuildingToBMP(ResourceType type) {
    CImg<unsigned char> SHEEP("./Images/GreenBuilding.BMP");
    CImg<unsigned char> STONE("./Images/GreyBuilding.BMP");
    CImg<unsigned char> TIMBER("./Images/RedBuilding.BMP");
    CImg<unsigned char> WHEAT("./Images/YellowBuilding.BMP");
    CImg<unsigned char> NONE("./Images/None.BMP");

    switch (type) {
    case ResourceType::NONE:
        return NONE;
    case ResourceType::SHEEP:
        return SHEEP;
    case ResourceType::STONE:
        return STONE;
    case ResourceType::WHEAT:
        return WHEAT;
    case ResourceType::TIMBER:
        return TIMBER;
    }
}

CImg<unsigned char> BuildingDownToBMP(ResourceType type) {
    CImg<unsigned char> SHEEP("./Images/GreenBuildingDown.BMP");
    CImg<unsigned char> STONE("./Images/GreyBuildingDown.BMP");
    CImg<unsigned char> TIMBER("./Images/RedBuildingDown.BMP");
    CImg<unsigned char> WHEAT("./Images/YellowBuildingDown.BMP");
    CImg<unsigned char> NONE("./Images/None.BMP");

    switch (type) {
    case ResourceType::NONE:
        return NONE;
    case ResourceType::SHEEP:
        return SHEEP;
    case ResourceType::STONE:
        return STONE;
    case ResourceType::WHEAT:
        return WHEAT;
    case ResourceType::TIMBER:
        return TIMBER;
    }
}

CImg<unsigned char> drawGBMap(GBMap& const gb_map, Player& const player)
{
    unsigned char black[] = { 0,0,0 };
    unsigned char white[] = { 1,1,1 };
    unsigned char vagueBrown[] = { 224,192,128 };

    CImg<unsigned char> MAP_TILE("./Images/TileNode.BMP");
    CImg<unsigned char> DISABLED_TILE("./Images/DisabledTile.BMP");
    CImg<unsigned char> RESOURCE_TRACKER("./Images/ResourceTracker.BMP");
    CImg<unsigned char> AVAILABLE_BUILDINGS("./Images/AvailableBuildings.BMP");

    CImg<unsigned char> GREY_TRACKER("./Images/GreyTracker.BMP");
    CImg<unsigned char> RED_TRACKER("./Images/RedTracker.BMP");
    CImg<unsigned char> YELLOW_TRACKER("./Images/YellowTracker.BMP");
    CImg<unsigned char> GREEN_TRACKER("./Images/GreenTracker.BMP");
   
    CImg<unsigned char> GREY_BUILDING("./Images/GreyBuilding.BMP");
    CImg<unsigned char> RED_BUILDING("./Images/RedBuilding.BMP");
    CImg<unsigned char> YELLOW_BUILDING("./Images/YellowBuilding.BMP");
    CImg<unsigned char> GREEN_BUILDING("./Images/GreenBuilding.BMP");

    CImg<unsigned char> VGMAP("./Images/VGMap.BMP");

    CImg<unsigned char> GRID;

    CImg<unsigned char> columns;
    columns = CImg<unsigned char>(25, 25, 1, 3, 0);


    for (int i = 0; i < gb_map.getTileGraph()->getLength(); i++) {
        CImg<unsigned char> column("./Images/Column.BMP");
        column.draw_text(50, 1, to_string(i).c_str(), black, vagueBrown, 1.0f, 22);
        columns.append(column);
    }
    GRID = columns;


    CImg<unsigned char> GBMAP;
    Node* m = gb_map.getTileGraph()->getNode(0);
    int rowCount = 0; 
    while(true){

        Node* n = m; 

        CImg<unsigned char> row("./Images/Row.BMP");

        row.draw_text(8,50, to_string(rowCount).c_str(),black,vagueBrown,1.0f,22);
        rowCount++;

        while (true) {
            CImg<unsigned char> tile;
            if (n->isEnabled()) {
                tile = MAP_TILE;

                for (int i = 0; i < 4; i++) {   
                    CImg<unsigned char> resource = ResourceToBMP(static_cast<Resource*>((static_cast<TileNode*>(n)->getResourceNodes()[i]))->getType());
                    switch (i) {
                    case 0:
                        tile.draw_image(0, 0, 0, resource, 100);
                        break;
                    case 1:
                        tile.draw_image(50, 0, 0, resource, 100);
                        break;
                    case 2:
                        tile.draw_image(0, 50, 0, resource, 100);
                        break;
                    case 3:
                        tile.draw_image(50, 50, 0, resource, 100);
                        break;  
                    }
                }
                
                row = row.append(tile, 'x');
            }
            else 
                row = row.append(DISABLED_TILE, 'x');
            

            if (n->getRight())
                n = n->getRight();
            else 
                break;
            
        }

        GRID = GRID.append(row, 'y');

        if (m->getDown())
            m = m->getDown();
        else {

            CImg<unsigned char> lastRow;

            while (true) {
                if (n->isEnabled()) 
                    lastRow = lastRow.append(MAP_TILE, 'x');
                else 
                    lastRow = lastRow.append(DISABLED_TILE, 'x');

                if (n->getRight())
                    n = n->getRight();
                else
                    break;
            }
            break;
        }
    }
    
    std::vector<Node*> vgNodes = player.getVGMap()->getBuildingGraph()->getNodes()[0];
    
    //18,23	return (row * length + col);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {

            CImg<unsigned char> buildingTile;
            if (static_cast<BuildingTile*>(vgNodes[j * 5 + i])->getFaceUp()) {
                buildingTile = BuildingToBMP(static_cast<BuildingTile*>(vgNodes[j * 5 + i])->getType());
                buildingTile.draw_text(3, 20, to_string(static_cast<BuildingTile*>(vgNodes[j * 5 + i])->getValue()).c_str(), black, 1, 1.0f, 40);
            }
            else
                buildingTile = BuildingDownToBMP(static_cast<BuildingTile*>(vgNodes[j * 5 + i])->getType());

            VGMAP.draw_image(18+93*i,23+93*j, 0, buildingTile, 100);
        }
    }
    // 235, 655
    VGMAP.draw_text(235, 655, player.getVGMap()->getName().c_str(), black, 1, 1.0f, 30);

    // Add hand info to bottom of grid
    CImg<unsigned char> HAND("./Images/Hand.BMP");
    CImg<unsigned char> tile = MAP_TILE;
    vector<HarvestTile*> tiles = player.getHand()->getHarvestHold()[0];

    for(int j = 0; j < tiles.size(); j++){

        for (int i = 0; i < 4; i++) {

            CImg<unsigned char> resource = ResourceToBMP(tiles[j]->getResources()[i]);
            switch (i) {
            case 0:
                tile.draw_image(0, 0, 0, resource, 100);
                break;
            case 1:
                tile.draw_image(50, 0, 0, resource, 100);
                break;
            case 2:
                tile.draw_image(50, 50, 0, resource, 100);
                break;
            case 3:
                tile.draw_image(0, 50, 0, resource, 100);
                break;
            }
        }
        HAND.draw_image(125*j,25,0,tile,100);
        HAND.draw_text(125*j, 25, to_string(j).c_str(), black, vagueBrown, 1.0f, 22);
    }

    vector<BuildingTile*> buildings = player.getHand()->getBuildingHold()[0];

    for (int i = 0; i < buildings.size(); i++) {


        CImg<unsigned char> building = BuildingToBMP(buildings[i]->getType())/*.resize_tripleXY().resize_halfXY().resize_halfXY()*/; 

        building.draw_text(4, 20, to_string(buildings[i]->getValue()).c_str(), black, 1, 1.0f, 28);

        int handRow = 0; 
        if (i > 5 && i < 12)
            handRow = 1;
        else if (i >= 12)
            handRow = 2;

        HAND.draw_image(80 * (i%6), 135 + 93*handRow, 0, building, 100);
        HAND.draw_text(80* (i%6), 135 + 93*handRow, to_string(i).c_str(), black, vagueBrown, 1.0f, 22);
    }

    GRID.append(HAND, 'y');;


    int stone = gb_map.getResourceTracker()[0][ResourceType::STONE];
    int timber = gb_map.getResourceTracker()[0][ResourceType::TIMBER];
    int wheat = gb_map.getResourceTracker()[0][ResourceType::WHEAT];
    int sheep = gb_map.getResourceTracker()[0][ResourceType::SHEEP];

    RESOURCE_TRACKER.draw_image(16, 670 - 33 * stone, GREY_TRACKER, 100); 
    RESOURCE_TRACKER.draw_image(35, 670 - 33 * timber, RED_TRACKER, 100);
    RESOURCE_TRACKER.draw_image(70, 670 - 33 * wheat, YELLOW_TRACKER, 100);
    RESOURCE_TRACKER.draw_image(91, 670 - 33 * sheep, GREEN_TRACKER, 100);


    GBMAP = RESOURCE_TRACKER.append(GRID).append(AVAILABLE_BUILDINGS).append(VGMAP);

    return GBMAP;


}





