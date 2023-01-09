#pragma once
#include "Room.hpp"
#define ROOM_TYPES 5 // numero di varianti di stanze disponibili
#define BOSS_FREQ 10 // vedi next_boss_room


//genera una stanza randomica con nemici di una data difficoltà
Room *random_room(int difficulty);

//genera una stanza contenente un nemico difficile, il nemico lascierà in terra un oggetto alla morte
Room *boss_room();

// data una stanza aggiunge nemici di difficoltà proporzionale al parametro difficulty
Room *add_hostiles(Room* r, int difficulty);

//aggiunge le chiavi e le posizioni alla stanza
Room *add_loot(Room *r);

//importa come chiuse dalle 0 alle 2 porte per la stanza r
Room *close_some_doors(Room *r);

//genera un id unico per la nuova stanza
int new_id();
