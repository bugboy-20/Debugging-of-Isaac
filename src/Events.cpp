#include "Events.hpp"
#include "RoomEvent.hpp"
#include "geometry.h"

// ENTITY_MOVE
EntityMoveE::EntityMoveE(coords old_pos, coords new_pos, char e) : RoomEvent(ENTITY_MOVE) {
    //... room actions
    this->data[0] = old_pos;
    this->data[1] = new_pos;
    this->ed = e;
}

// ENTITY_KILLED
EntityKilledE::EntityKilledE(Entity *e) : RoomEvent(ENTITY_KILLED) {
    this->data = e;
}

void EntityKilledE::destroy() {
    delete this->data;
}

// ROOM_CHANGED
RoomChangedE::RoomChangedE() : RoomEvent(ROOM_CHANGED) {}

// PLAYER_HEALTH_CHANGED
PlayerHealthChangedE::PlayerHealthChangedE(Player *p) : RoomEvent(PLAYER_HEALTH_CHANGED) {
    this->data = p;
}

// ENTITY_DAMAGED
EntityDamagedE::EntityDamagedE(Entity *e) : RoomEvent(ENTITY_DAMAGED) {
    this->data = e;
}

// INVENTORY_CHANGED
InventoryChangedE::InventoryChangedE() : RoomEvent(INVENTORY_CHANGED) {}

ItemPickedE::ItemPickedE(ItemOnGround *i) : RoomEvent(ITEM_PICKED) {
    this->data = i;
}

void ItemPickedE::destroy() {
    delete this->data;
}


ItemDroppedE::ItemDroppedE(coords c) : RoomEvent(ITEM_DROPPED){
    this->data=c;
}
