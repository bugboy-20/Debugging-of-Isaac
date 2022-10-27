#include "Bullet.hpp"
#include "physics.h"
#include "Events.hpp"

#ifdef _WIN32 // sleep fn
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

char bullet_name[10] = "bullet";
char bullet_desc[20] = "bullet_desc";

Bullet::Bullet(coords pos) : Entity(pos, '.', bullet_desc, bullet_name, 5000, 0) {}

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