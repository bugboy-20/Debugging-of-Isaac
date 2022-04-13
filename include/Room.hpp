#pragma once

#include "Core.hpp"
#include "Entity.hpp"
#include "List.hpp"
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
        List get_room_member(); // restituisce una lista con tutti i membri della stanza
        door *door[4];

    private:
        int id;

};
