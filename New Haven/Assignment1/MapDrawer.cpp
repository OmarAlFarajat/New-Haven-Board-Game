#include "MapDrawer.h"

using namespace cimg_library;
using std::cout;
using std::endl; 
void drawGBMap(GBMap& gb_map)
{
    CImg<unsigned char> MAP_TILE("TileNode.BMP");
    CImg<unsigned char> DISABLED_TILE("DisabledTile.BMP");

    // Declare output and intermediate variables
    CImg<unsigned char> grid;

    Node* m = gb_map.getTileGraph()->getNode(0);

    while(true){

        Node* n = m; 
        CImg<unsigned char> row; 

        while (true) {

            if (n->isEnabled()) {
                cout << "Enabled\t";
                row = row.append(MAP_TILE, 'x');
            }
            else {
                cout << "X\t";
                row = row.append(DISABLED_TILE, 'x');
            }

            if (n->getRight())
                n = n->getRight();
            else {
                //if (n->isEnabled()) {
                //    cout << "Enabled\t";
                //    row = row.append(MAP_TILE, 'x');
                //}
                //else {
                //    cout << "X\t";
                //    row = row.append(DISABLED_TILE, 'x');
                //}
                break;
            }
        }

        cout << "~~~ Appending row to grid" << endl;
        grid = grid.append(row, 'y');

        if (m->getDown())
            m = m->getDown();
        else {

            CImg<unsigned char> lastRow;

            while (true) {
                cout << "appending lastRow" << endl;
                if (n->isEnabled()) {
                    cout << "Enabled\t";
                    lastRow = lastRow.append(MAP_TILE, 'x');
                }
                else {
                    cout << "X\t";
                    lastRow = lastRow.append(DISABLED_TILE, 'x');
                }
                
                if (n->getRight())
                    n = n->getRight();
                else
                    break;
            }
            cout << "appending lastGrid" << endl;
            grid = grid.append(lastRow, 'y');
            break;
        }
    }
    

    // Append horizontally into a row, you could append many - you are not restricted to 2
    //row0 = row0.append(_IMG, 'x').append(_IMG, 'x').append(_IMG, 'x').append(_IMG, 'x').append(_IMG, 'x');

    // Append vertically into a column
    //grid = grid.append(row0, 'y').append(row0, 'y').append(row0, 'y').append(row0, 'y').append(row0, 'y');

    grid.display();
}
