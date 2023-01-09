#include "Screen.hpp"

#include <iostream>
#include <locale.h>
#ifdef _WIN32 // sleep fn
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
    clear();
    getmaxyx(stdscr, stdscr_height, stdscr_width);

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
    game_menu = newwin(stdscr_height / 2, stdscr_width / 2, stdscr_height / 4, stdscr_width / 4);
    // box(game_menu, 0, 0);
    wrefresh(game_menu);

    this->gm = GameMenu(game_menu, stdscr_width / 2, stdscr_height / 2);
}

void Screen::start_gameinterface(Room *r)
{
    // attivo il nodelay
    nodelay(stdscr, TRUE);

    int lateral_width = 22,
        lower_height = 10,
        playerstat_height = 9,
        inventory_height = 6,
        legend_height = ROOM_HEIGHT + lower_height - playerstat_height - inventory_height,
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
    this->gi.set_room(r);
    this->gi.render_room();
    this->gi.render_inventory();
    this->gi.render_legend();
    this->gi.render_moblist();
    this->gi.render_playerstat();
}

void Screen::start_gamecontrols()
{
    controls = newwin(stdscr_height / 2, stdscr_width / 3, stdscr_height / 4, stdscr_width / 3);
    wrefresh(controls);
    this->gc = GameControls(controls);
}
// void Screen::do_screen(Room *r)
// {
//     this->gi.set_room(r);
//     this->gi.handle_events();
// }

int Screen::print_game_over()
{
    wclear(inventory);
    wclear(legend);
    wclear(moblist);
    wclear(wroom);
    wclear(playerstat);

    wnoutrefresh(inventory);
    wnoutrefresh(legend);
    wnoutrefresh(moblist);
    wnoutrefresh(wroom);
    wnoutrefresh(playerstat);
    doupdate();

    /*
 _______    _______    _______    _______
(  ____ \  (  ___  )  (       )  (  ____ \
| (    \/  | (   ) |  | () () |  | (    \/
| |        | (___) |  | || || |  | (__
| | ____   |  ___  |  | |(_)| |  |  __)
| | \_  )  | (   ) |  | |   | |  | (
| (___) |  | )   ( |  | )   ( |  | (____/\
(_______)  |/     \|  |/     \|  (_______/

 _______               _______    _______
(  ___  )  |\     /|  (  ____ \  (  ____ )
| (   ) |  | )   ( |  | (    \/  | (    )|
| |   | |  | |   | |  | (__      | (____)|
| |   | |  ( (   ) )  |  __)     |     __)
| |   | |   \ \_/ /   | (        | (\ (
| (___) |    \   /    | (____/\  | ) \ \__
(_______)     \_/     (_______/  |/   \__/
*/

    int text_height = 17, text_width = 42, current_y = (stdscr_height - text_height) / 2 - 3, current_x = (stdscr_width - text_width) / 2;
    nodelay(stdscr, FALSE);
    mvprintw(current_y, current_x, "%s", " _______    _______    _______    _______ ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "(  ____ \\  (  ___  )  (       )  (  ____ \\");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| (    \\/  | (   ) |  | () () |  | (    \\/");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| |        | (___) |  | || || |  | (__    ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| | ____   |  ___  |  | |(_)| |  |  __)   ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| | \\_  )  | (   ) |  | |   | |  | (      ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| (___) |  | )   ( |  | )   ( |  | (____/\\");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "(_______)  |/     \\|  |/     \\|  (_______/");
    current_y += 2;
    // mvprintw(current_y, current_y, "%s", "                                          ");
    mvprintw(current_y, current_x, "%s", " _______               _______    _______ ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "(  ___  )  |\\     /|  (  ____ \\  (  ____ )");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| (   ) |  | )   ( |  | (    \\/  | (    )|");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| |   | |  | |   | |  | (__      | (____)|");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| |   | |  ( (   ) )  |  __)     |     __)");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| |   | |   \\ \\_/ /   | (        | (\\ (   ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "| (___) |    \\   /    | (____/\\  | ) \\ \\__");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "(_______)     \\_/     (_______/  |/   \\__/");
    mvprintw(stdscr_height - 5, 0, "%s %c %s", "Premi un tasto per ricominciare oppure premi", quit_button, "per uscire...");
    refresh();
    int key;
    do
    {
        key = getch();
    } while (key != 'n' && key != quit_button);
    return key;
}

void Screen::stop_screen()
{
    endwin();
}
