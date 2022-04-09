#include "Map.h"
#include "Room.h"

struct map game_map;

struct map *init_map(room starting_room)
{
    room *ptr_start_room = new room;
    *ptr_start_room = starting_room;

    game_map.current_room = ptr_start_room;
    game_map.rooms = ptr_start_room;

    return &game_map;
}

void change_room(room *new_room)
{
    game_map.current_room = new_room;
}
