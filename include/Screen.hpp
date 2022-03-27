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
    int test;
    
    void printDoors(door *doors[]);


public:
    Screen();
    // stampa sullo schermo l'intera stanza
    void renderRoom(room r);

    // stampa sullo schermp solo gli elementi che possono spostarsi (muri ecc)
    void updateRoom(room r); // per ora propongo entrambi i metodi
                             // ma si può anche scegliere di usare un solo metodo se preferite

    void stopScreen();
};
