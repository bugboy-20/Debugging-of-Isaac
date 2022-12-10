#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "Room.hpp"

struct interface_coords
{
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
};

class GameInterface
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    WINDOW *debug; // schermo temporaneo per i messaggi di debug
    Room *r;
    interface_coords i_coords;
    bool newEvents;

public:
    GameInterface() = default;
    GameInterface(WINDOW *, WINDOW *, WINDOW *, WINDOW *, WINDOW *, interface_coords);

    // aggiorna il puntatore locale con quello della room da visualizzare
    void set_room(Room *r);
    // controlla gli eventi in coda e li smaltisce
    void handle_events();

    // metodi per le singole finestre
    /**
     * Prende come parametro una Room, pulisce lo schermo, stampa le porte,
     * e poi stampa gli elementi della stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza
     */
    void render_room();

    /**
     * Stampa il riquadro in cui sono visualizzati punteggio e vita.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * inizia il gioco, la vita del player aumenta o diminuisce, il player guadagna punti
     *
     */
    void render_playerstat();

    /**
     * Stampa una legenda con elementi presenti nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza
     *
     */
    void render_legend();

    /**
     * Stampa la sezione con la vita e il nome di tutti gli ostili nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza, un hostile prende danno, un hostile muore
     *
     */
    void render_moblist();

    /**
     * Stampa la sezione in cui sono rappresentati gli oggetti raccolti dal giocatore.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * ancora non lo so
     *
     */
    void render_inventory();

    // metodi di utilità
    /**
     * Stampa le porte
     *
     * @param doors array di porte da stampare
     */
    void print_doors(door *doors[]);
};
