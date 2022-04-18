#pragma once

#include "Core.hpp"
#include "Entity.hpp"
#include "List.hpp"
#include "Player.hpp"
#include "Room.h"
#include "geometry.h"

class Room {
    public:
        Room(int id, List entities, List cores); /* inizializzazione con lista di elementi
                                                    ATTENZIONE! le liste vengono consumate
                                                 */
        Room(int id);
        Core *get_element_in_this_position(coords); //data una posizione restituisce l'elemento che si trova in essa, NULL se non vi è nulla.
        int get_id();
        void add_Core(Core *); //aggiunge un elemento alla stanza (non vivo)
        void add_entity(Entity *); // aggiunge una entità alla stanza
        void delete_room_menber(Core *); // elimina un elemento della stanza (funziona anche con le entità
        List get_room_member(); // restituisce una lista con tutti i membri della stanza, player è in testa
        List get_entities(bool player_too); // restituisce una lista con tutte le entità se il booleano è `true` essa comprende anche il player
        door *door[4];

        Room *next_room(enum door_pos); // restituisce la stanza nella direzione selezionata
                                        // NULL se vi è un muro

    private:
        int id;
        Player *p;
        List entities;
        List core;
        List walls;

};
