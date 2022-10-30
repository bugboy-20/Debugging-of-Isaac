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

Bullet::Bullet(coords pos, int damage) : Entity(pos, bullet_display, bullet_desc, bullet_name, 5000, damage) {}
