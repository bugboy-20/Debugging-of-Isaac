#pragma once
#include "Player.hpp"
#include "Room.hpp"
#include <iostream>
using namespace std;

bool collision(int x, int y, Room r);

bool door_collision(int x, int y, Room r);

bool general_collision(coords pos, Room r);

void do_room(Room *r); // fa cose sulla stanza

bool game_over(Player p);