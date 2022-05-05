#include "EntityMoveE.hpp"
#include "RoomEvent.hpp"
#include "geometry.h"

EntityMoveE::EntityMoveE(coords old_pos, coords new_pos) : RoomEvent(ENTITY_MOVE) {
    //... room actions
    this->data[0] = old_pos;
    this->data[1] = new_pos;
}
