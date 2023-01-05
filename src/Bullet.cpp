#include "Bullet.hpp"
#include "physics.h"
#include "constants.h"
#include "Events.hpp"

Bullet::Bullet(coords pos, int damage, direction direction, int range) : Entity(pos, bullet_display, bullet_d, {damage, 5000, 0, 150, range})
{
    this->d = direction;
    this->space_travelled = 0;
}

int Bullet::get_direction() { return this->d; }
void Bullet::set_direction(enum direction direction) { this->d = direction; };

move_outcome Bullet::move(Room *r, int x, int y)
{
    move_outcome out = Entity::move(r, x, y);
    if (this->space_travelled >= this->range && out != TIMEOUT)
        return COLLISION;
    if (out == MOVEMENT)
        space_travelled += 1;
    return out;
}

move_outcome Bullet::move_up(Room *room) { return this->move(room, 0, -1); }
move_outcome Bullet::move_down(Room *room) { return this->move(room, 0, 1); }
move_outcome Bullet::move_left(Room *room) { return this->move(room, -1, 0); }
move_outcome Bullet::move_right(Room *Room) { return this->move(Room, 1, 0); }