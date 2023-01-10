#include <cstdlib>
#include <cstddef>
#include "Room_handle.h"
#include "Hostile.hpp"
#include "HostileList.hpp"


static int id=0; // generazione di un ID unico per ogni stanza

int new_id() {
    return id++;
}

Room *boss_room() {
    Room *r = new Room(new_id());
    //nessuna porta, è una stanza "foglia"

    int lv = r->get_id()/10;
    Hostile *boss;
    Item *i;

    switch (rand()%5) {
        case 0:
            i = new Weapon('/',"Spada-pistola",lv);
            break;
        case 1:
            i = new Armor('T',"Elmo di mia zia",lv);
            break;
        case 2:
            i = new Boots('L',"Scarpine fatate",lv);
            break;
        case 3:
            i = new Crosshair('X',"Occhio di Lucertola",lv);
            break;
        case 4:
            i = new Booster('>',"Speeeed",lv);
            break;
    }

    switch(rand()%3) {
        case 0: boss = new Golem(safe_random_spawn(*r),0,i); break;
        case 1: boss = new Mago(safe_random_spawn(*r),0,i); break;
        case 2: boss = new Drago(safe_random_spawn(*r),0,i); break;
    }
    r->add_entity(boss);

    return r;
}

// I calcoli sono stati eseguiti su carta, quindi fidatevi

/*   _____  _____
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

/*   _____  _____
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




#define return_room_N(N) case N: return close_some_doors(add_hostiles( add_loot( room ## N()), difficulty)); break;

Room *random_room(int difficulty) {
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

coords safe_random_spawn(Room& r) {
    int x,y;
    do{
        x=1 + rand()%(ROOM_WIDTH-1);
        y=1 + rand()%(ROOM_HEIGHT-1);
    } while(r.get_element_in_this_position({x,y})!=NULL);

    return {x,y};
}

Room *add_loot(Room *r) {

    const int potion_probabitilty = pot_spwan_rate;
    const int key_probability = key_spawn_rate;
    coords c;
    Potion *p;
    Key *k;
    ItemOnGround *i;

    while(rand()%100 < potion_probabitilty) {
        c = safe_random_spawn(*r);
        
        p = new Potion();
        i = new ItemOnGround(c,p);
        r->add_items_on_ground(i);
    }

    while(rand()%100 < key_probability) {
        c = safe_random_spawn(*r);

        k = new Key();
        i = new ItemOnGround(c,k);
        r->add_items_on_ground(i);
    }

    return r;
}

Room *add_hostiles(Room* r, int difficulty) {
    int lv,i=difficulty;
    coords p;
    Hostile *h;

    while(i>=0) {
        p=safe_random_spawn(*r);


        lv=rand()%(i+1);
        i-=lv+1; //entità di livello 0 (virtualmente) potrebbero essere generate infinitamente

        switch (rand()%7) {
			case 0: h = new Zombie(p,lv); break;
			case 1: h = new Scheletro(p,lv); break;
			case 2: h = new Goblin(p,lv); break;
			case 3: h = new Fantasma(p,lv); break;
			case 4: h = new Ragno(p,lv); break;
			case 5: h = new Mummia(p,lv); break;
            case 6: h = new Torretta(p,lv); break;
        }


        r->add_entity(h);
    }
    return r;
}

/* questa funzione prende in input una stanza e chiude da 0 a 2 porte */
Room *close_some_doors(Room *r) {

    int door_closed = rand() % 2;
    int i=0;
    door *d;

    while (i<door_closed) {
        d=r->door[rand()%4];
        
        if(d==NULL) //porta non esistente, riprova
            continue;

        d->locked=true;
        i++;
    }
    return r;
}



