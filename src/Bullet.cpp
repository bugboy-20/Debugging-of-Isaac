#include "Bullet.hpp"
#include "physics.h"
#include "constants.h"
#include "Events.hpp"

char bullet_name[STR_LENGTH] = bullet_n;
char bullet_desc[STR_LENGTH] = bullet_d;

Bullet::Bullet(coords pos, int damage, direction direction, int range) : Entity(pos, bullet_display, bullet_desc, bullet_name, {damage, 5000, 0, 150, range})
{
    this->d = direction;
    this->space_travelled = 0;
}

int Bullet::get_direction() { return this->d; }
void Bullet::set_direction(enum direction direction) { this->d = direction; };

bool Bullet::move(Room *r, int x, int y)
{
    coords n_pos = {this->pos.x + x, this->pos.y + y};
    timeval now;
    time_now(now);
    // se non posso muovermi termino e ritorno che non ho avuto collisione
    if (time_elapsed(last_move, now) < movement_speed)
        return true;
    // se posso muovermi controllo se collido con qualcosa
    if (!collision(this->pos.x + x, this->pos.y + y, *r) && this->space_travelled < this->range)
    {
        r->add_event(new EntityMoveE(pos, n_pos, this->get_display()));
        this->pos.x += x;
        this->pos.y += y;
        this->last_move = now;
        this->space_travelled += 1;
        return true;
    }
    else
        return false;
}

bool Bullet::move_up(Room *room) { return move(room, 0, -1); }
bool Bullet::move_down(Room *room) { return move(room, 0, 1); }
bool Bullet::move_left(Room *room) { return move(room, -1, 0); }
bool Bullet::move_right(Room *Room) { return move(Room, 1, 0); }
// TODO trovare un modo per implementare il range