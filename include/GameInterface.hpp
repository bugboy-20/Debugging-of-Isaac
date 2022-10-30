#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "Room.hpp"

class GameInterface
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    Room *r;

public:
    GameInterface() = default;
    GameInterface(WINDOW *, WINDOW *, WINDOW *, WINDOW *, WINDOW *);

    // aggiorna il puntatore locale con quello della room da visualizzare
    void set_room(Room &r);
    // controlla gli eventi in coda e li smaltisce
    void update_interface();

    // metodi per le singole finestre
    void render_room();
    void render_playerstat();
    void render_legend();
    void render_moblist();
    void render_inventory();
};
