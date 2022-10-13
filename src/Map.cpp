#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "List.hpp"
#include "Events.hpp"
#include "Wall.hpp"
#include "Map.h"
#include "Player.hpp"
#include "Room.hpp"

#define ROOM_TYPES 1 // numero di varianti di stanze disponibili
struct map game_map;

Room *room1();

int id=0; // generazione di un ID unico per ogni stanza
int new_id() {
    return id++;
}
struct map *init_map(Player *p)
{
    std::cout << "caca";
    Room *ptr_start_room = room1();// new Room(new_id());
    std::cout << "pupu";
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


Room *room1() {

    List wl = List();

    Wall *w1 = new Wall({{ROOM_HEIGHT / 2, ROOM_WIDTH / 4}, false, ROOM_WIDTH / 4});
    //Wall *w2 = new Wall({{ROOM_HEIGHT / 2, ROOM_WIDTH / 4}, true, ROOM_HEIGHT / 4 -1});

    wl.push(w1);
    //wl.push(w2);

    Room *r = new Room(new_id(), wl);

    return r;
};

Room *room0() {

    List wl = List();

    Wall *w1 = new Wall({{ROOM_HEIGHT / 2, ROOM_WIDTH / 4}, true, ROOM_WIDTH / 4});

    wl.push(w1);

    Room *r = new Room(new_id(), wl);

    return r;
}


Room *random_room() {
    srand(time(0));
    switch (rand()%ROOM_TYPES) {
        case 0:
            return room0();
        default:
            return new Room(new_id());
    }
    rand();
}
