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

Bullet::Bullet(coords pos, int damage) : Entity(pos, '.', bullet_desc, bullet_name, 5000, damage) {}
