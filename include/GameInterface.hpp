#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "Room.hpp"

class GameInterface
{
private:
    WINDOW *wroom, *playerstat, *legend, *moblist, *inventory;
    Room *r;

public:
    GameInterface() = default;
    GameInterface(WINDOW *, WINDOW *, WINDOW *, WINDOW *, WINDOW *);

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
     *
     * @param r la stanza che viene stampata
     */
    void render_room();

    /**
     * Stampa il riquadro in cui sono visualizzati punteggio e vita.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * inizia il gioco, la vita del player aumenta o diminuisce, il player guadagna punti
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_playerstat();

    /**
     * Stampa una legenda con elementi presenti nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_legend();

    /**
     * Stampa la sezione con la vita e il nome di tutti gli ostili nella stanza.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * si cambia stanza, un hostile prende danno, un hostile muore
     *
     * @param r la stanza da cui prende le informazioni
     */
    void render_moblist();

    /**
     * Stampa la sezione in cui sono rappresentati gli oggetti raccolti dal giocatore.
     *
     * Funzione che dovrebbe essere chiamata quando:
     * ancora non lo so
     *
     * @param r la stanza da cui prende le informazioni
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
