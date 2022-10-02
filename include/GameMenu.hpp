#pragma once
#include <ncursesw/ncurses.h>

class GameMenu
{
private:
    WINDOW *win;
    int num_menu,
        selected_menu,
        width,
        height;
    const char *menus[]; // deve essere l'ultimo elemento perchè la dimensione è dinamica

public:
    GameMenu();
    void draw();
    void stop();
    void select_next_item();
    void select_prev_item();
};