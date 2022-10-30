#include "Bullet.hpp"
#include "physics.h"
#include "Events.hpp"
#include "constants.h"
#ifdef _WIN32 // include temporaneao
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

char bullet_name[STR_LENGTH] = bullet_n;
char bullet_desc[STR_LENGTH] = bullet_d;

Bullet::Bullet(coords pos) : Entity(pos, bullet_display, bullet_desc, bullet_name, 5000, 0) {}

bool Bullet::shoot(Room *r, int x, int y)
{

    coords n_pos = {this->pos.x + x, this->pos.y + y};
    if (!collision(this->pos.x + x, this->pos.y + y, *r))
    {
        this->pos.y = this->pos.y + 1;
        r->add_event(new EntityMoveE(pos, n_pos, this->get_display()));
        return true;
    }
    else
        return false;
}