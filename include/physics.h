#pragma once
#include "Player.hpp"
#include "Room.hpp"

bool collision(int x, int y, Room& r);

bool wall_collision(coords pos, Room& r);

bool general_collision(coords pos, Room& r);

void door_collision(coords pos, Room& r);

void next_room_position(Room& r, enum door_pos p);

void do_room(Room *r); // fa cose sulla stanza

bool game_over(Player p);
