#pragma once

#include "Player.hpp"
#include "Room.hpp"

struct map
{
    Room *current_room;
     /* puntatore alla prima stanza, tutte le altre sono collegate dalle porte
                  * Porta linka a doppia direzione le stanze
                  */
    Room *rooms;
};

// inizializza la mappa, restituisce un puntatore alla mappa il cui uso è facoltativo.
// inizializza la mappa inserendo il player in una stanza vuota
map *init_map(Player *p);

// cambia la stanza in cui il personaggio si trova in quella passata per indirizzo dalla funzione
void change_room(Room *new_room);
