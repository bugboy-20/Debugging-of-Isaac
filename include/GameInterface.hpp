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
    Room *r;
    interface_coords i_coords;

    // metodi di utilità
    /**
     * Stampa le porte
     *
     * @param doors array di porte da stampare
     */
    void print_doors(door *doors[]);
    /**
     * prende in input un carattere e se è migliorabile restituisce la versione migliore,
     * altrimenti lo lascia inalterato
     * 
     * @param char carattere da migliorare
     * @return carattere migliorato oppure lo stesso carattere passato in input
    */
    chtype improve_char(char);

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
     * inizia il gioco, la vita del player aumenta o diminuisce, il player guadagna punti,
     * una statistica del player cambia
     */
    void render_playerstat();

    /**
     * Stampa una legenda con elementi presenti nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza, viene droppato un oggetto
     */
    void render_legend();

    /**
     * Stampa la sezione con la vita e il nome di tutti gli ostili nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza, un hostile prende danno, un hostile muore
     */
    void render_moblist();

    /**
     * Stampa la sezione in cui sono rappresentati gli oggetti raccolti dal giocatore.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * quando raccolgo un oggetto (sia pozione, che chiave, che item), quando lascio un oggetto
     */
    void render_inventory();
};
