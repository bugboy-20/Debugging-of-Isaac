#pragma once
#include "geometry.h"
#include "constants.h"

class Core
{
protected:
    coords pos;
    char display;
    char description[STR_LENGTH];
    bool crossable; // se questo è `true` l'elemento è una decorazione del pavimento

public:
    Core(coords pos, char display, const char description[STR_LENGTH], bool crossable = false);
    int get_x();
    int get_y();
    char get_display();
    char *get_description();
    void get_description(char[STR_LENGTH]);
    bool is_crossable();
};
