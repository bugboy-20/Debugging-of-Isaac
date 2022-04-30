#pragma once

#include "Core.hpp"
#include "Entity.hpp"
#include "List.hpp"
#include "Player.hpp"
#include "Room.h"
#include "geometry.h"

class Room {
    public:
         /* inizializzazione con lista di elementi
            ATTENZIONE! le liste vengono consumate
         */
        Room(int id, List entities, List cores);
        Room(int id);
 //data una posizione restituisce l'elemento che si trova in essa, NULL se non vi è nulla.
        Core *get_element_in_this_position(coords);
        int get_id();
//aggiunge un elemento alla stanza (non vivo)
        void add_Core(Core *);
// aggiunge una entità alla stanza
        void add_entity(Entity *);
// elimina un elemento della stanza (funziona anche con le entità
        void delete_room_menber(Core *);
// restituisce una lista con tutti i membri della stanza, player è in testa
        List get_room_member();
// restituisce una lista con tutte le entità se il booleano è `true` essa comprende anche il player
        List get_entities(bool player_too);
        struct door *door[4];
        Player *p;

// restituisce la stanza nella direzione selezionata
// NULL se vi è un muro
        Room *next_room(enum door_pos); 
                                        

    private:
        int id;
        List entities;
        List core;
        List walls;

};
