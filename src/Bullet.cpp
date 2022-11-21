#include "Bullet.hpp"
#include "physics.h"
#include "constants.h"

char bullet_name[STR_LENGTH] = bullet_n;
char bullet_desc[STR_LENGTH] = bullet_d;

Bullet::Bullet(coords pos, int damage, direction direction, int range) : Entity(pos, bullet_display, bullet_desc, bullet_name, {damage, 5000, 0, 150, range})
{
    this->d = direction;
    this->space_travelled = 0;
}

int Bullet::get_direction() { return this->d; }
void Bullet::set_direction(enum direction direction) { this->d = direction; };

// TODO trovare un modo per implementare il range