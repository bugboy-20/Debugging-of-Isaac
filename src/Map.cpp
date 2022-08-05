#include <cstddef>
#include "List.hpp"
#include "Events.hpp"
#include "Wall.hpp"
#include "Map.h"
#include "Player.hpp"
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
        ptr_start_room->door[i]=new door;
        ptr_start_room->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        ptr_start_room->door[i]->next_room=NULL;
    }

    ptr_start_room->p=p;
    
    game_map.rooms=ptr_start_room;
    game_map.current_room=game_map.rooms;


    ptr_start_room->add_event(new RoomChangedE()); //avviso lo schermo che c'è una nuova stanza da renderizzare
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

//TODO: far si che le stanze non siano sempre vuote
//TODO: aggiungere consistenza e non violare le leggi di Euclide e del buon senso
Room *add_room(Room *r, enum door_pos p) {
    int i;
    door *d = r->door[p];
    Room *new_room = new Room(new_id());

    d->next_room=new_room;

    switch (d->position) {
UPPER_DOOR:
        i=LOWER_DOOR;
        break;
RIGHT_DOOR:
        i=LEFT_DOOR;
        break;
LOWER_DOOR:
        i=UPPER_DOOR;
        break;
LEFT_DOOR:
        i=RIGHT_DOOR;
    }

    new_room->door[i]=new door;
    new_room->door[i]->position=i;
    new_room->door[i]->next_room=r;

    return new_room;

}



Room *room0() {

    List wl = List();

    char desc[20] = "muro di pietra";
    Wall *w1 = new Wall({{ROOM_HEIGHT / 2, ROOM_WIDTH / 4}, true, ROOM_WIDTH / 4}, '#', desc);

    wl.push(w1);

    Room *r = new Room(new_id(), wl);

    return r;
}
