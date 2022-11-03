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

Bullet::Bullet(coords pos, int damage) : Entity(pos, bullet_display, bullet_desc, bullet_name, 5000, damage)
{
    this->movement_speed = 150;
    this->last_move = high_resolution_clock::now(); // il primo controllo è (time(0) - 0 >= attack_speed) che è sempre vero
    this->direction = 4;
}

system_clock::time_point Bullet::get_last_move() { return this->last_move; }
void Bullet::set_last_move(system_clock::time_point lm) { this->last_move = lm; }

int Bullet::get_movement_speed() { return this->movement_speed; }
void Bullet::set_movement_speed(int ms) { this->movement_speed = ms; }

int Bullet::get_direction(){ return this->direction; }
void Bullet::set_direction(int direction){ this->direction = direction; };