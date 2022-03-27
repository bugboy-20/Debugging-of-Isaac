#pragma once

#include "Room.h"

struct map
{
    room *current_room;
    room *rooms; /* puntatore alla prima stanza, tutte le altre sono collegate dalle porte
                  * Porta linka a doppia direzione le stanze
                  */
};

// inizializza la mappa, restituisce un puntatore alla mappa il cui uso è facoltativo.
// quando la mappa viene inizializzata crea una stanza come quella in input.
map *init_map(room starting_room);

// cambia la stanza in cui il personaggio si trova in quella passata per indirizzo dalla funzione
void change_room(room *new_room);
