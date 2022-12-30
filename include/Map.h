#pragma once

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
// level deve essere >= 1
map *init_map(Player *p, int level);

// cambia la stanza in cui il personaggio si trova in quella passata per indirizzo dalla funzione
void change_room(Room *new_room);

// aggiunge una stanza dopo la porta
// in input vuole la stanza e la posizione della porta dove va aggiunta la stanza
//      questa so che ha una forma strana ma mi sembrava più difficile da usare male
Room *add_room(Room *r, enum door_pos p);

//porta la mappa allo stato {NULL,NULL} e dealloca le stanze
void destroy_map(map);
