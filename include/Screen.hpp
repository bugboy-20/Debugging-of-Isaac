#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "Room.hpp"

class Screen
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    int flag;

    bool newEvents;

    int lateral_width,
        lower_height,
        playerstat_height,
        legend_height,
        inventory_height,
        moblist_width,
        start_x,
        start_y,
        lateral_start_x,
        lower_start_y;

    /**
     * Inizializza le window e disegna i bordi per ognuna
     */
    void windows_init();

    /**
     * Stampa le porte
     *
     * @param doors array di porte da stampare
     */
    void print_doors(door *doors[]);

    /**
     * Prende come parametro una Room, pulisce lo schermo, stampa le porte,
     * e poi stampa gli elementi della stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza
     *
     * @param r la stanza che viene stampata
     */
    void render_room(Room &r);

    /**
     * Stampa il riquadro in cui sono visualizzati punteggio e vita.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * inizia il gioco, la vita del player aumenta o diminuisce, il player guadagna punti
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_playerstat(Room &r);

    /**
     * Stampa una legenda con elementi presenti nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_legend(Room &r);

    /**
     * Stampa la sezione con la vita e il nome di tutti gli ostili nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza, un hostile prende danno, un hostile muore
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_moblist(Room &r);

    /**
     * Stampa la sezione in cui sono rappresentati gli oggetti raccolti dal giocatore.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * ancora non lo so
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_inventory(Room &r);

public:
    /**
     * Costruttore della classe schermo
     * Inizializza ncurses e le tutte le finestre
     */
    Screen();

    /**
     * Aggiorna lo schermo in base agli eventi che avvenuti
     *
     * @param r l'oggetto room da cui prende le informazioni
     */
    void do_screen(Room *r);

    /**
     * Termina lo schermo
     */
    void stop_screen();
    WINDOW *debug; // schermo temporaneo per i messaggi di debug

};
