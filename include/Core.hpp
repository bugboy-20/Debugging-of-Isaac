#pragma once
#include "geometry.h"

class Core
{
protected:
    coords pos;
    char display;

public:
    Core(coords pos, char display);
    int get_x();
    int get_y();
    char get_display();
};
