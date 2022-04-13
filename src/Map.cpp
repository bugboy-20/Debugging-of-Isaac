#include <cstddef>
#include "Map.h"
#include "Room.h"

struct map game_map;

int id=0; // generazione di un ID unico per ogni stanza
int new_id() {
    return id++;
}
struct map *init_map(room starting_room)
{
    room *ptr_start_room = new room;
    *ptr_start_room = starting_room;
    ptr_start_room->id=id;
    id++;

    game_map.current_room = ptr_start_room;
    game_map.rooms = ptr_start_room;

    return &game_map;
}

void change_room(room *new_room)
{
    new_room->player=game_map.current_room->player;
    game_map.current_room->player = NULL;
    game_map.current_room = new_room;
}
