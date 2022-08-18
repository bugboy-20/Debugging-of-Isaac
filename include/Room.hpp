#pragma once

#include "Core.hpp"
#include "Entity.hpp"
#include "List.hpp"
#include "Player.hpp"
//#include "Room.h"
#include "Wall.hpp"
#include "geometry.h"
#include "RoomEvent.hpp"
#include "Queue.hpp"

#define ROOM_HEIGHT 20
#define ROOM_WIDTH 100

enum door_pos
{
    UPPER_DOOR,
    RIGHT_DOOR,
    LOWER_DOOR,
    LEFT_DOOR
};

struct door
{
    int position; // es LEFT_DOOR o RIGHT_DOOR
    Room *next_room;
};

class Room {
    public:
         /* inizializzazione con lista di elementi
            ATTENZIONE! le liste vengono consumate
         */
        Room(int id, List walls, List entities, List cores);
        Room(int id, List walls);
        Room(int id);

 //data una posizione restituisce l'elemento che si trova in essa, NULL se non vi è nulla.
        Core *get_element_in_this_position(coords);
        int get_id();

//aggiunge un elemento alla stanza (non vivo)
        void add_Core(Core *);

// aggiunge una entità alla stanza
        void add_entity(Entity *);

// aggiunge una entità alla stanza
        void add_wall(Wall *);

// elimina un elemento della stanza (funziona anche con le entità)
// NB. non viene deallocato l'elemento in se
        void delete_room_menber(Core *);

// restituisce una lista con tutti i membri della stanza, player è in testa
        List get_room_member();

// restituisce una lista con tutte le entità se il booleano è `true` essa comprende anche il player
        List get_entities(bool player_too);

// restituisce una lista contenete i muri della stanza
        List get_walls();

        struct door *door[4];
        Player *p;

// restituisce la stanza nella direzione selezionata
// NULL se vi è un muro
        Room *next_room(enum door_pos); 
                                        
// aggiungi un evento alla coda degli eventi
        void add_event(RoomEvent *e);

// toglie dalla coda un evento
        RoomEvent *get_event();

        //debug
        void prinmt_room_menmb();

    private:
        int id;
        List entities;
        List core;
        List walls;
    
        Queue events;

};
