#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "GameMenu.hpp"
#include "GameInterface.hpp"

class Screen
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory, *game_menu;

    int stdscr_width, stdscr_height;

public:
    /**
     * Costruttore della classe schermo
     * Inizializza ncurses e le tutte le finestre
     */
    GameMenu gm;
    GameInterface gi;

    Screen();

    /**
     * inizializza il menu
     */
    void start_gamemenu();
    /**
     * Inizializza le window e disegna i bordi per ognuna
     */
    void start_gameinterface(Room *);

    /**
     * Aggiorna lo schermo in base agli eventi che avvenuti
     *
     * @param r l'oggetto room da cui prende le informazioni
     */
    // void do_screen(Room *r);

    /**
     * Termina lo schermo
     */
    void stop_screen();
};
