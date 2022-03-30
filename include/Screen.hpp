#pragma once

#include <iostream>

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "Room.h"

class Screen
{
private:
    WINDOW *wroom;
    int room_height, room_width;

    void printDoors(door *doors[]);

public:
    Screen();
    // stampa sullo schermo l'intera stanza
    void renderRoom(room r);

    // spegne lo schermo
    void stopScreen();
};
