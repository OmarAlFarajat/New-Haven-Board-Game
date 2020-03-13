#include "MapDrawer.h"

using std::cout;
using std::endl; 

CImg<unsigned char> ResourceToBMP(ResourceType type) {
    CImg<unsigned char> SHEEP("Sheep.BMP");
    CImg<unsigned char> STONE("Stone.BMP");
    CImg<unsigned char> TIMBER("Timber.BMP");
    CImg<unsigned char> WHEAT("Wheat.BMP");
    CImg<unsigned char> NONE("None.BMP");
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

void drawGBMap(GBMap& gb_map)
{
    CImg<unsigned char> MAP_TILE("TileNode.BMP");
    CImg<unsigned char> DISABLED_TILE("DisabledTile.BMP");
    CImg<unsigned char> RESOURCE_TRACKER("ResourceTracker.BMP");
    CImg<unsigned char> AVAILABLE_BUILDINGS("AvailableBuildings.BMP");

    CImg<unsigned char> GREY_TRACKER("GreyTracker.BMP");
    CImg<unsigned char> RED_TRACKER("RedTracker.BMP");
    CImg<unsigned char> YELLOW_TRACKER("YellowTracker.BMP");
    CImg<unsigned char> GREEN_TRACKER("GreenTracker.BMP");


    CImg<unsigned char> GRID;
    CImg<unsigned char> GBMAP;
    Node* m = gb_map.getTileGraph()->getNode(0);

    while(true){

        Node* n = m; 
        CImg<unsigned char> row; 


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
    int stone = gb_map.getResourceTracker()[0][ResourceType::STONE];
    int timber = gb_map.getResourceTracker()[0][ResourceType::TIMBER];
    int wheat = gb_map.getResourceTracker()[0][ResourceType::WHEAT];
    int sheep = gb_map.getResourceTracker()[0][ResourceType::SHEEP];

    RESOURCE_TRACKER.draw_image(16, 670 - 33 * stone, GREY_TRACKER, 100); 
    RESOURCE_TRACKER.draw_image(35, 670 - 33 * timber, RED_TRACKER, 100);
    RESOURCE_TRACKER.draw_image(70, 670 - 33 * wheat, YELLOW_TRACKER, 100);
    RESOURCE_TRACKER.draw_image(91, 670 - 33 * sheep, GREEN_TRACKER, 100);


    GBMAP = RESOURCE_TRACKER.append(GRID).append(AVAILABLE_BUILDINGS);
    GBMAP.display();
}





