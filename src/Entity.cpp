#include "Entity.hpp"
#include "Room.h"
#include "physics.h"
#include <cstring>
#include <ncursesw/ncurses.h>

Entity::Entity(char name[10], int health, int damage, coords pos, char display,bool is_player) : Core(pos, display)
{
  strcpy(this->name, name);
  this->health = health;
  this->damage = damage;
  this->is_player = is_player;
};

bool Entity::move_up(room room)
{
  return move(room, 0, -1);
};
bool Entity::move_down(room room)
{
  return move(room, 0, 1);
};
bool Entity::move_left(room room)
{
  return move(room, -1, 0);
};
bool Entity::move_right(room room)
{
  return move(room, 1, 0);
};
bool Entity::move(const room r, int x, int y)
{
  if (!collision(this->pos.x + x, this->pos.y + y, r))
  {
    this->pos.x += x;
    this->pos.y += y;
    return true;
  }
  else
    return false;
};

void Entity::action(){};
int Entity::get_damage() { return damage; };
int Entity::get_health() { return health; };
char[10] Entity::get_name() { return name; };