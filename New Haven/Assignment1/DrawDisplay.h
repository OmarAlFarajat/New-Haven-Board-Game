#pragma once
#include "CImg.h"
#include "MapDrawer.h"

using cimg_library::CImgDisplay;

// CIMG Main Display
extern CImgDisplay main_disp;
extern int main_disp_x;
extern int main_disp_y;
extern MapDrawer* drawer;
extern void UpdateDisplay();