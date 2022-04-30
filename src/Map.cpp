#include <cstddef>
#include "Map.h"
#include "Player.hpp"
#include "Room.h"
#include "Room.hpp"

struct map game_map;

int id=0; // generazione di un ID unico per ogni stanza
int new_id() {
    return id++;
}
struct map *init_map(Player *p)
{
    Room *ptr_start_room = new Room(new_id());
    
    for (int i=0; i<4; i++) {
        ptr_start_room->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        ptr_start_room->door[i]->next_room=NULL;
    }

    ptr_start_room->p=p;
    
    game_map.rooms=ptr_start_room;
    game_map.current_room=game_map.rooms;

    return &game_map;
}

void change_room(Room *new_room)
{
    //sposto il player
    new_room->p=game_map.current_room->p;
    game_map.current_room->p=NULL;

    //cambio stanza attuale
    game_map.current_room=new_room;

}
