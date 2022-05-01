#pragma once
#include "Room.h"
#include "Room.hpp"

bool collision(int x, int y, Room r);

void do_room(Room *r); // fa cose sulla stanza

bool game_over();