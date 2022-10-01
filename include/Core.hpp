#pragma once
#include "geometry.h"

class Core
{
protected:
    coords pos;
    char display;
    char description[20];
    bool crossable; // se questo è `true` l'elemento è una decorazione del pavimento

public:
    Core(coords pos, char display, char description[]); // DEPRECATO: lo tengo per non star ad alterare tutto il codice già scritto
    Core(coords pos, char display, char description[], bool crossable);
    int get_x();
    int get_y();
    char get_display();
    char *get_description();
    void get_description(char[20]);
};
