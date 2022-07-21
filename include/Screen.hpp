#pragma once

#include <iostream>

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "Room.h"
#include "Room.hpp"

class Screen
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    // *legend, *moblist, *playerstat, *inventory
    int current_room_id;
    bool x;

    void print_doors(door *doors[]);
    /**
     * It creates a bunch of windows and draws boxes around them
     */
    void windows_init();
    /**
     * It takes a Room object as a parameter, clears the screen, draws the walls and doors, and then draws
     * the characters in the room
     *
     * @param r the room to be drawn
     */
    void room_init(Room r);

public:
    Screen();

    // stampa sullo schermo la stanza
    // void render_room(room r);
    void render_room(Room r);

    // stampa il riquadro in cui sono visualizzati punteggio e vita
    void render_playerstat(room r);

    // stampa una legenda degli elementi presenti nella stanza
    void render_legend(room r);

    // stampa la sezione con la vita di tutti gli ostili nella stanza
    void render_moblist(room r);

    // stampa la sezione in cui sono rappresentati gli oggetti raccolti dal giocatore
    void render_inventory(room r);

    // spegne lo schermo
    void stop_screen();
};
