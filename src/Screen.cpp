#include "Screen.hpp"

#include <iostream>
#include <locale.h>

#define rgbtc(c) (int)(c / (51 / 200.0)) // trasforma un valore rgb 0-255 in scala 0-1000
#define DEFAULT 0
Screen::Screen()
{
    setlocale(LC_ALL, ""); // dovrebbe servire per stampare caratteri speciali, ma non va. TODO documentarsi meglio
    initscr();
    cbreak();             // ctrl+c behaviour
    noecho();             // avoids user input from being printed
    curs_set(0);          // rende invisibile il cursore
    keypad(stdscr, true); // permette l'utilizzo del arrow_key
    // nodelay(stdscr, TRUE); // il nodelay viene attivato sono nel gioco

    /* initialize colors */
    if (!has_colors())
    {
        endwin();
        std::cerr << "Your terminal does not support color" << std::endl;
        exit(EXIT_FAILURE);
    }
    start_color();
    int COLOR_DEFAULT_BG = -1, COLOR_DEFAULT_FG = -1;
    if (use_default_colors() == ERR)
    {
        COLOR_DEFAULT_BG = COLOR_BLACK;
        COLOR_DEFAULT_FG = COLOR_WHITE;
    }

    if (can_change_color())
    {
        // cambio i colori per i terminale che li supportano
        init_color(COLOR_WHITE, rgbtc(140), rgbtc(140), rgbtc(140));  // gray
        init_color(COLOR_CYAN, rgbtc(22), rgbtc(100), rgbtc(0));      // green
        init_color(COLOR_BLUE, rgbtc(34), rgbtc(8), rgbtc(156));      // blue
        init_color(COLOR_GREEN, rgbtc(112), rgbtc(7), rgbtc(232));    // purple
        init_color(COLOR_YELLOW, rgbtc(202), rgbtc(102), rgbtc(5));   // orange
        init_color(COLOR_MAGENTA, rgbtc(153), rgbtc(101), rgbtc(21)); // gold
        init_color(COLOR_RED, rgbtc(239), rgbtc(11), rgbtc(11));      // red
    }
    // std::cerr << COLORS << " " << COLOR_PAIRS << std::endl;
    init_pair(DEFAULT, COLOR_DEFAULT_FG, COLOR_DEFAULT_BG);
    init_pair(lvl1, COLOR_WHITE, COLOR_DEFAULT_BG);
    init_pair(lvl2, COLOR_CYAN, COLOR_DEFAULT_BG);
    init_pair(lvl3, COLOR_BLUE, COLOR_DEFAULT_BG);
    init_pair(lvl4, COLOR_GREEN, COLOR_DEFAULT_BG);
    init_pair(lvl5, COLOR_YELLOW, COLOR_DEFAULT_BG);
    init_pair(lvl6, COLOR_MAGENTA, COLOR_DEFAULT_BG);
    init_pair(lvl7, COLOR_RED, COLOR_DEFAULT_BG);

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

    this->gi = GameInterface(wroom, playerstat, legend, moblist, inventory,
                             {lateral_width,
                              lower_height,
                              playerstat_height,
                              legend_height,
                              inventory_height,
                              moblist_width,
                              start_x,
                              start_y,
                              lateral_start_x,
                              lower_start_y});
}

// void Screen::do_screen(Room *r)
// {
//     this->gi.set_room(r);
//     this->gi.handle_events();
// }

void Screen::stop_screen()
{
    // delwin(wroom);
    // delwin(playerstat);
    // delwin(legend);
    // delwin(moblist);
    // delwin(inventory);
    endwin();
}
