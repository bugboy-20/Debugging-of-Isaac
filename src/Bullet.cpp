#include "Bullet.hpp"
#include "physics.h"
#include "Events.hpp"

#ifdef _WIN32 // sleep fn
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

Bullet::Bullet(char name[10], int health, int damage, coords pos, char display, char description[]) : Entity(name,health,damage,pos,display,description) {}
bool Bullet::shoot(Room *r, int x, int y){

    coords n_pos = {this->pos.x + x, this->pos.y + y};
    if (!collision(this->pos.x + x, this->pos.y + y, *r)){
    this->pos.y = this->pos.y + 1;
    r->add_event(new EntityMoveE(pos, n_pos, this->get_display()));
    return true;
    }else return false;

}

void Bullet::set_x(int x){
    this->pos.x = x;
}

void Bullet::set_y(int y){
    this->pos.y = y;
}