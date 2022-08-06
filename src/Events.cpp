#include "Events.hpp"

#include "Entity.hpp"
#include "RoomEvent.hpp"
#include "geometry.h"

// ENTITY_MOVE
EntityMoveE::EntityMoveE(coords old_pos, coords new_pos) : RoomEvent(ENTITY_MOVE) {
    //... room actions
    this->data[0] = old_pos;
    this->data[1] = new_pos;
}



// ENTITY_KILLED
EntityKilledE::EntityKilledE(Entity *e) : RoomEvent(ENTITY_KILLED) {
    this->data = e;
}

EntityKilledE::~EntityKilledE() {
    delete this->data;
}


// ROOM_CHANGED
RoomChangedE::RoomChangedE() : RoomEvent(ROOM_CHANGED) {}


// PLAYER_DAMAGED
PlayerDamagedE::PlayerDamagedE(Player *p) : RoomEvent(PLAYER_DAMAGED) {
    this->data = p;
}

PlayerDamagedE::~PlayerDamagedE() {
    delete this->data;
}