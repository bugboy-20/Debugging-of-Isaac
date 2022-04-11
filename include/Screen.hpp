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
    WINDOW *wroom, *playerstat, *legend;
    // *legend, *moblist, *playerstat, *inventory

    void print_doors(door *doors[]);

public:
    Screen();

    // stampa sullo schermo l'intera stanza
    void render_room(room r);

    void render_playerstat(room r);

    // spegne lo schermo
    void stop_screen();
};
