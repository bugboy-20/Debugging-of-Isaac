#include "GameMenu.hpp"
#include <cstring>

GameMenu::GameMenu()
{
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    curs_set(0);
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    // init windows
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    this->width = xMax / 2;
    this->height = yMax / 2;
    win = newwin(height, width, yMax / 4, xMax / 4);
    box(win, 0, 0);
    wrefresh(win);

    // init variables
    this->num_menu = 2;
    this->selected_menu = 0;
    this->menus[0] = "Nuova Partita";
    this->menus[1] = "Esci dal Gioco";

    // print title
    char str[] = "Super Mario Galaxy";
    int length = strlen(str), pad;
    if (length >= width)
        pad = 0;
    else
        pad = (width - length) / 2;

    mvwprintw(win, height * 0.2, pad, str);

    refresh();
    wrefresh(win);
    // wgetch(win);
}

void GameMenu::draw()
{
    // print menu options
    box(win, 0, 0);

    int start_y = this->height * 0.4;
    for (int i = 0; i < this->num_menu; i++)
    {
        int length = strlen(this->menus[i]), pad;
        if (length >= this->width)
            pad = 0;
        else
            pad = (width - length) / 2;

        if (selected_menu == i)
        {
            // wprintw(win, "lul:%d ", this->selected_menu);
            wattron(win, A_STANDOUT);
        }
        mvwprintw(win, start_y, pad, this->menus[i]);
        wattroff(win, A_STANDOUT);
        start_y += 2;
    }
    wrefresh(win);
}

void GameMenu::select_next_item()
{
    this->selected_menu += 1;
    if (this->selected_menu >= num_menu)
        this->selected_menu = 0;
}

void GameMenu::select_prev_item()
{
    this->selected_menu -= 1;
    if (this->selected_menu < 0)
        this->selected_menu = num_menu - 1;
}

void GameMenu::stop()
{
    clear();
    wclear(win);
    // endwin();
}