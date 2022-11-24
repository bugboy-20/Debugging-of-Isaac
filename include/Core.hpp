#pragma once
#include "geometry.h"
#include "constants.h"

class Core
{
protected:
    coords pos;
    char display;
    char description[20];
    bool crossable; // se questo è `true` l'elemento è una decorazione del pavimento

public:
    Core(coords pos, char display, char description[], bool crossable = false);
    int get_x();
    int get_y();
    char get_display();
    char *get_description();
    void get_description(char[20]);
    bool is_crossable();
};
