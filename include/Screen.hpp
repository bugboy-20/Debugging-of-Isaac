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
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    // *legend, *moblist, *playerstat, *inventory
    int current_room_id;

    void print_doors(door *doors[]);
    void windows_init();

public:
    Screen();

    // stampa sullo schermo la stanza
    void render_room(room r);

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
