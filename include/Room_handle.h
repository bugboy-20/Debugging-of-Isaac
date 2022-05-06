#pragma once

#include "Room.hpp"

#define BOSS_ROOM_RATE 10

Room random_room(int id); //genera una stanza casuale. Rispetta la generazione delle stanze boss ogni BOSS_ROOM_RATE
