#pragma once

#include "RoomEvent.hpp"
#include "Room.hpp"
#include "geometry.h"
class EntityMoveE : public RoomEvent {
    public:
        EntityMoveE(coords old_pos, coords new_pos);
        coords data[2];
};

