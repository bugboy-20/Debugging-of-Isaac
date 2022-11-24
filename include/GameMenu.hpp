#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#define STRLEN 20
enum menu_elem
{
    NEW_GAME,
    EXIT_GAME,
};

class GameMenu
{
private:
    WINDOW *win;
    int num_menu,
        selected_menu,
        width,
        height;
    char menus[EXIT_GAME + 1][STRLEN];

public:
    GameMenu() = default;
    GameMenu(WINDOW *, int, int);
    void draw();
    void select_next_item();
    void select_prev_item();
    int get_selected_item();
    void clean();
};
