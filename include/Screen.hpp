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

    void print_doors(door *doors[]);

public:
    Screen();

    // stampa sullo schermo l'intera stanza
    void render_room(room r);
    // spegne lo schermo
    void stop_screen();
};
