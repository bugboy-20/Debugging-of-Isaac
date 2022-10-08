#include "GameMenu.hpp"
#include <cstring>

GameMenu::GameMenu(WINDOW *w, int width, int height)
{
    // init variables
    this->win = w;
    this->num_menu = EXIT_GAME + 1; // exit game e` l'ultimo elemento
    this->selected_menu = NEW_GAME;
    strcpy(menus[NEW_GAME], "Nuova Partita");
    strcpy(menus[EXIT_GAME], "Esci dal Gioco");

    this->width = width;
    this->height = height;

    // print title
    char str[] = "Super Mario Galaxy";
    int length = strlen(str), pad;
    if (length >= width)
        pad = 0;
    else
        pad = (width - length) / 2;

    mvwprintw(win, height * 0.2, pad, str);

    wrefresh(this->win);
}

void GameMenu::draw()
{
    // print menu options
    int start_y = this->height * 0.4;
    for (int i = 0; i < this->num_menu; i++)
    {
        int length = strlen(this->menus[i]), pad;
        if (length >= this->width)
            pad = 0;
        else
            pad = (width - length) / 2;

        if (selected_menu == i)
            wattron(win, A_STANDOUT);

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

int GameMenu::get_selected_item()
{
    return this->selected_menu;
}

void GameMenu::clean()
{
    wclear(win);
    wrefresh(win);
}
