#pragma once
#include <ncursesw/ncurses.h>
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

    // stampa sullo schermp solo gli elementi che possono spostarsi (muri ecc)
    void updateRoom(room r); // per ora propongo entrambi i metodi
                             // ma si può anche scegliere di usare un solo metodo se preferite

    void stopScreen();
};
