#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "RoomEvent.hpp"
#include "geometry.h"

/*
 * collezione di tutti gli eventi
 */

// evento una entità s'è mossa
class EntityMoveE : public RoomEvent {
    public:
        EntityMoveE(coords old_pos, coords new_pos);
        coords data[2];
};

// evento una entità è stata eliminata
class EntityKilledE : public RoomEvent {
    public:
        EntityKilledE(Entity *e);
        void destroy();
        Entity *data;
};

// evento stanza cambiata
class RoomChangedE : public RoomEvent {
    public:
        RoomChangedE();
};

// evento player perde vita
class PlayerHealthChangedE : public RoomEvent {
    public:
        PlayerHealthChangedE(Player *p);
        Player *data;
};

// evento una entità(non player) ha perso vita
class EntityDamagedE : public RoomEvent {
    public: 
        EntityDamagedE(Entity *e);
        Entity *data;
};
