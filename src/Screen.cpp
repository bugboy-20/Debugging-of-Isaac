#include "Screen.hpp"

#include <locale.h>

Screen::Screen()
{
    setlocale(LC_ALL, ""); // dovrebbe servire per stampare caratteri speciali, ma non va. TODO documentarsi meglio
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    // nodelay(stdscr, TRUE);
    curs_set(0);
    intrflush(stdscr, FALSE);
    keypad(stdscr, true);
    refresh();
}

void Screen::start_gamemenu()
{
    // init windows
    getmaxyx(stdscr, stdscr_height, stdscr_width);
    game_menu = newwin(stdscr_height / 2, stdscr_width / 2, stdscr_height / 4, stdscr_width / 4);
    // box(game_menu, 0, 0);
    wrefresh(game_menu);

    this->gm = GameMenu(game_menu, stdscr_width / 2, stdscr_height / 2);
}

void Screen::start_gameinterface()
{
    // attivo il nodelay
    nodelay(stdscr, TRUE);

    int lateral_width = 20,
        lower_height = 10,
        playerstat_height = 4,
        legend_height = (ROOM_HEIGHT + lower_height - playerstat_height) / 2,
        inventory_height = ROOM_HEIGHT + lower_height - playerstat_height - legend_height,
        moblist_width = ROOM_WIDTH,
        start_x = 1,
        start_y = 0,
        lateral_start_x = ROOM_WIDTH + 1 + start_x,
        lower_start_y = ROOM_HEIGHT;

    wroom = newwin(ROOM_HEIGHT, ROOM_WIDTH, start_y, start_x);
    playerstat = newwin(playerstat_height, lateral_width, start_y, lateral_start_x);
    legend = newwin(legend_height, lateral_width, playerstat_height + start_y, lateral_start_x);
    inventory = newwin(inventory_height, lateral_width, playerstat_height + legend_height + start_y, lateral_start_x);
    moblist = newwin(lower_height, moblist_width, lower_start_y + start_y, start_x);
    box(wroom, 0, 0);
    box(playerstat, 0, 0);
    box(legend, 0, 0);
    box(inventory, 0, 0);
    box(moblist, 0, 0);

    // refresh();
    wnoutrefresh(wroom);
    wnoutrefresh(playerstat);
    wnoutrefresh(legend);
    wnoutrefresh(moblist);
    wnoutrefresh(inventory);
    doupdate();

    this->gi = GameInterface(wroom, playerstat, legend, moblist, inventory);
}

// void Screen::do_screen(Room *r)
// {
//     this->gi.set_room(r);
//     this->gi.handle_events();
// }

void Screen::stop_screen()
{
    endwin();
}
