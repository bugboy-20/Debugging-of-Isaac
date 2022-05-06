#include "Entity.hpp"
#include "EntityMoveE.hpp"
#include "Room.h"
#include "Room.hpp"
#include "RoomEvent.hpp"
#include "physics.h"
#include <cstring>

Entity::Entity(char name[10], int health, int damage, coords pos, char display) : Core(pos, display)
{
  strcpy(this->name, name);
  this->health = health;
  this->damage = damage;
};

bool Entity::move_up(Room room)
{
  return move(room, 0, -1);
};
bool Entity::move_down(Room room)
{
  return move(room, 0, 1);
};
bool Entity::move_left(Room room)
{
  return move(room, -1, 0);
};
bool Entity::move_right(Room Room)
{
  return move(Room, 1, 0);
};
bool Entity::move(Room r, int x, int y)
{
  if (!collision(this->pos.x + x, this->pos.y + y, r))
  {
    r.add_event((RoomEvent *) new EntityMoveE(this->pos,{this->pos.x+x,this->pos.y+y}));
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
char *Entity::get_name()
{
  char *nome = new char[10];
  strcpy(nome, name);
  return nome;
};

char *get_name();
