#pragma once
#include "geometry.h"

class Core
{
protected:
    coords pos;
    char display;
    char description[20];

public:
    Core(coords pos, char display, char description[]);
    int get_x();
    int get_y();
    char get_display();
    char *get_description();
};
