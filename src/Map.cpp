#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Events.hpp"
#include "Map.h"
#include "Room_handle.hpp"

static struct map game_map;
static int difficulty;
static bool next_boss_room = false; // ogni BOSS_FREQ stanze la prossima stanza generata è una boss_room

struct map *init_map(Player *p, int level)
{
    srand(time(0));

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
        
        difficulty=game_map.current_room->p->get_score()/10;

    }
}

void create_loop(Room *starting_room, int direction, bool clockwise=true) {
    /*
     * viene effettuata una visita scegliendo sempre la porta che si trova a destra (o sinistra) di quella da cui si è entranti
     * se la visita ad anello passa per 3 stanze allora l'ultima porta deve portare alla stanza di partenza
     * +---------+---------+
     * |         |         |
     * |         |         |
     * |    ^  --+->       |
     * |    |    |    |    |
     * +----+----+----+----+
     * |    |    |    |    |
     * |       <-+--  v    |
     * |         |         |
     * |         |         |
     * +---------+---------+
     */
    Room *r_ptr=starting_room;
    int next_door,i;
    for(i=0; i<3;i++) {
        if(clockwise)
            next_door=(direction+i)%4;
        else
            next_door=(direction-i+4)%4;


        if (r_ptr->door[next_door] == NULL || r_ptr->door[next_door]->next_room == NULL)
            return;

        r_ptr = r_ptr->door[next_door]->next_room;
    }

    if(clockwise)
        next_door=(direction+i)%4;
    else
        next_door=(direction-i+4)%4;
    if(r_ptr->door[next_door]==NULL)
        return;

    r_ptr->door[next_door]->next_room=starting_room;
    starting_room->door[(next_door +2) % 4]->next_room = r_ptr;

}

Room *add_room(Room *r, enum door_pos p) {
    int i=0;
    door *d = r->door[p];
    Room *new_room = next_boss_room ? boss_room() : random_room(difficulty);

    next_boss_room = false; //se ho generato una boss_room adesso deve tornare false.

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
     */
    if (new_room->door[i]==NULL)
        new_room->door[i]=new door;

    new_room->door[i]->position=i;
    new_room->door[i]->next_room=r;
    new_room->door[i]->locked=false;

    // INDIRECT LINKING
    /*
     * questa parte si occupa di fare in modo che Player movendosi ad anello si ritrovi nella stanza di partenza.
     * create_loop loop fa una visita in senso orario ed antiorario per ogni porta
     */
    for(int iter=0; iter<4; iter++) {
        create_loop(new_room, i, true);
        create_loop(new_room, i, false);
    }


    if(new_room->get_id() % BOSS_FREQ == BOSS_FREQ - 1)
        next_boss_room = true;

    return new_room;

}


void destroy_map(map m) {
    door *d;
    int porta_reciproca;
    /*
     * Esegue una visita in profondità, ogni volta che accede ad una nuova stanza 
     *
     * per prima cosa elimina i puntatori entranti affinchè sucessivamente non si vengano a creare loop o errori di segmentazione
     */
    for(int i=0; i<4; i++) {
        d = m.current_room->door[i];
        if (d==NULL || d->next_room == NULL)
            continue;
        porta_reciproca = (d->position + 2) % 4;
        d->next_room->door[porta_reciproca]=NULL;
    }

    // svuota la stanza
    m.current_room->empty();

    // ripeto ricorsivamente su tutte le stanze adiacienti [ancora esistenti e non scollegate]
    // l'assenza di nuove stanze da raggiungere è il caso base 
    for (int i=0; i<4; i++) {
        d=m.current_room->door[i];
        if (d!=NULL && d->next_room !=NULL) {
            destroy_map({d->next_room, m.rooms});
            delete d;
            m.current_room->door[i]=NULL;
        }
    }

    // elimino la stanza
    delete m.current_room;
}
