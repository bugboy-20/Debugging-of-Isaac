#pragma once
#include "Room.hpp"
#define ROOM_TYPES 5 // numero di varianti di stanze disponibili
#define BOSS_FREQ 10 // vedi next_boss_room


Room *random_room(int difficulty);
Room *boss_room();
Room *add_hostiles(Room* r, int difficulty);
Room *add_loot(Room *r);
Room *close_some_doors(Room *r);

int new_id();
