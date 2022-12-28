#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Core.hpp"
#include "Entity.hpp"
#include "Hostile.hpp"
#include "HostileList.hpp"
#include "List.hpp"
#include "Events.hpp"
#include "Wall.hpp"
#include "Map.h"
#include "Player.hpp"
#include "Room.hpp"
#include "physics.h"

#define ROOM_TYPES 5 // numero di varianti di stanze disponibili
static struct map game_map;
static int difficulty;

Room *room1();
Room *random_room();

Room *add_hostiles(Room* r);

static int id=0; // generazione di un ID unico per ogni stanza
int new_id() {
    return id++;
}
struct map *init_map(Player *p, int level)
{
    srand(time(0));

    difficulty=(level-1)*1000; // TODO bilanciare

    Room *ptr_start_room = new Room(new_id());
    for (int i=0; i<4; i++) {
        ptr_start_room->door[i]=new door;
        ptr_start_room->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        ptr_start_room->door[i]->next_room=NULL;
        ptr_start_room->door[i]->locked=false;
    }

    ptr_start_room->p=p;
    
    game_map.rooms=ptr_start_room;
    game_map.current_room=game_map.rooms;


    ptr_start_room->add_event(new RoomChangedE()); //avviso lo schermo che c'è una nuova stanza da renderizzare
    return &game_map;
}

void change_room(Room *new_room)
{
    if (new_room != NULL) {
        //sposto il player
        new_room->p=game_map.current_room->p;
        game_map.current_room->p=NULL;

        //cambio stanza attuale
        game_map.current_room=new_room;
        new_room->add_event(new RoomChangedE());
    }
    else {
        fprintf(stderr, "si è cercato di accedere ad una stanza nulla\n");
    }

}



//TODO: aggiungere consistenza e non violare le leggi di Euclide e del buon senso
Room *add_room(Room *r, enum door_pos p) {
    int i=0;
    door *d = r->door[p];
    Room *new_room = random_room();

    d->next_room=new_room;

    //LINKING

    i = (d->position + 2) % 4;
    /*
     *  Essendo gli enum valori interi position ha valore tra 0 e 3
     *
     *      U
     *  Le      R
     *      Lo
     *
     *  immaginando le porte nella posizione data dall'enum si nota che rappresentano un anello, per cui possiamo ricondurci ad una soluzione in algebra modulare.
     *
     *  VECCHIO CODICE:
     */
    /*switch (d->position) {
        case UPPER_DOOR:
            i=LOWER_DOOR;
            break;
        case RIGHT_DOOR:
            i=LEFT_DOOR;
            break;
        case LOWER_DOOR:
            i=UPPER_DOOR;
            break;
        case LEFT_DOOR:
            i=RIGHT_DOOR;
            break;
    }*/

    /* CODICE MORTO?
    if (new_room == NULL)
        new_room->door[i]=new door;
    */
    new_room->door[i]->position=i;
    new_room->door[i]->next_room=r;
    new_room->door[i]->locked=false;

    // INDIRECT LINKING


    //for(int d_pos=i; 


    return new_room;

}

// I calcoli sono stati eseguiti su carta, quindi fidatevi

/*
 *   _____  _____
 *  |            |
 *  |            |
 *
 *  |            |
 *  |_____  _____|
 */
Room *room0() {

    Room *r = new Room(new_id());

    for (int i=0; i<4; i++) {
        r->door[i]=new door;
        r->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        r->door[i]->next_room=NULL;
        r->door[i]->locked=false;
    }


    return r;
}

/*
 *   _____  _____
 *  |         |  |
 *  |         |  |
 *      |     |
 *  |   |        |
 *  |___|_  _____|
 */
Room *room1() {

    List wl = List();

    int xshift = (1.0/5.0)* ROOM_WIDTH;
    int yshift =  (1.0/3.0)* ROOM_HEIGHT;

    int xw1 = xshift + rand()%xshift;
    int yw1 = yshift + rand()%yshift;
    int l = ROOM_HEIGHT - yw1 - 2;

    line lw1 = { { xw1, yw1} , true, l};
    line lw2 = { {ROOM_WIDTH - xw1, 1}, true, l};
    Wall *w1 = new Wall(lw1);
    Wall *w2 = new Wall(lw2);

    std::cerr << "(x,y,l)=(" << xw1 << "," << yw1 << "," << l << ")" << std::endl;
    wl.push(w1);
    wl.push(w2);



    Room *r = new Room(new_id(), wl);

    for (int i=0; i<4; i++) {
        r->door[i]=new door;
        r->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        r->door[i]->next_room=NULL;
        r->door[i]->locked=false;
    }


    return r;
}

/*
 *   _____  _____
 *  |   |        |
 *  |            |
 *      |      
 *  |   |        |
 *  |___|_  _____|
 */
Room *room2() {

    List wl = List();

    int xshift = 0.3 * ROOM_WIDTH;

    int x1 = (.2)* ROOM_WIDTH + rand()%xshift -2;
    int y1 = 1;
    int l1 = 1 + rand()%(ROOM_HEIGHT-3);

    int x2 = x1;
    int y2 = l1 + 4;
    int l2 = ROOM_HEIGHT - y2 - 2;

    line lw1 = { { x1, y1} , true, l1};
    line lw2 = { { x2, y2}, true, l2};
    Wall *w1 = new Wall(lw1);
    Wall *w2 = new Wall(lw2);

    wl.push(w1);
    wl.push(w2);



    Room *r = new Room(new_id(), wl);

    for (int i=0; i<4; i++) {
        r->door[i]=new door;
        r->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        r->door[i]->next_room=NULL;
        r->door[i]->locked=false;
    }


    return r;
}
/*
 *   _____  _____
 *  |            |
 *  |   O    O   |
 *
 *  |       O    |
 *  |_____  _____|
 */
char ssasso[] = "sasso";

Room *room3() {


    Room *r = new Room(new_id());

    int n_sasso = 2 + rand()%10;

// #define x_range (ROOM_WIDTH/4 + rand()%(ROOM_WIDTH/4))
// #define y_range (ROOM_HEIGHT/4 + rand()%(ROOM_HEIGHT/4))
#define x_range (2 + rand()%(ROOM_WIDTH - 4))
#define y_range (2 + rand()%(ROOM_HEIGHT - 4))


    for (int i=0; i<n_sasso; i++) {
        Core *sasso = new Core({x_range,y_range},'O', ssasso);
        r->add_Core(sasso);
    }

    for (int i=0; i<4; i++) {
        r->door[i]=new door;
        r->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        r->door[i]->next_room=NULL;
        r->door[i]->locked=false;
    }

#undef x_range
#undef y_range

    return r;
}

/* TODO sistemare la circolarità
 *   _____  _____
 *  |            |
 *  |     O      |
 *      O   O
 *  |     O      |
 *  |_____  _____|
 */
Room *room4() {

    Room *room = new Room(new_id());

    int r= 1 + rand()%5;

    for (int i=-2*r; i< 2*r; i++)
        for (int j=-2*r; j< 2*r; j++)
            if( ((float)(i*i/2.0) + j*j < r*r))
                room->add_Core(new Core({ROOM_WIDTH/2 + i, ROOM_HEIGHT/2 + j},'O',ssasso));

    for (int i=0; i<4; i++) {
        room->door[i]=new door;
        room->door[i]->position=i; // UPPER_DOOR ecc. hanno un valore intero tra 0 e 3 
        room->door[i]->next_room=NULL;
        room->door[i]->locked=false;
    }


    return room;
}




#define return_room_N(N) case N: return add_hostiles( room ## N()); break;

Room *random_room() {
    switch (rand()%ROOM_TYPES) {
        return_room_N(0);
        return_room_N(1);
        return_room_N(2);
        return_room_N(3);
        return_room_N(4);
        default:
            return new Room(new_id());
    }
}



Room *add_hostiles(Room* r) {
    int x,y,lv;
    for(int i=difficulty; i<0;) {
        do {
            x=rand()%ROOM_WIDTH;
            y=rand()%ROOM_HEIGHT;
        } while(collision(x, y, *r));

        lv=rand()%i;
        i-=lv;

        Hostile *h = new Zombie({x,y},lv);
        r->add_entity(h);
    }
    return r;
}
