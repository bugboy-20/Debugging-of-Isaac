#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "RoomEvent.hpp"
#include "geometry.h"

/*
 * collezione di tutti gli eventi
 */

//envento una entità s'è mossa
class EntityMoveE : public RoomEvent {
    public:
        EntityMoveE(coords old_pos, coords new_pos);
        coords data[2];
};

//evento una entità è stata eliminata
class EntityKilledE : public RoomEvent {
    public:
        EntityKilledE(Entity *e);
        ~EntityKilledE();
        Entity *data;
};

// evento stanza cambiata
class RoomChangedE : public RoomEvent {
    public:
        RoomChangedE();
};

// evento player perde vita
class PlayerDamagedE : public RoomEvent {
    public:
        PlayerDamagedE(Player *p);
        ~PlayerDamagedE();
        Player *data;
};
