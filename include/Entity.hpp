#pragma once
#include "Core.hpp"
#include "Room.hpp"

class Entity : public Core
{

protected:
  char name[10];
  int health;
  int damage;

public:
  Entity(char name[10], int health, int damage, coords pos, char display);
  bool move_up(Room Room);
  bool move_down(Room Room);
  bool move_left(Room Room);
  bool move_right(Room Room);
  void action();

  char* get_name();
  int get_health();
  int get_damage();
private:
  bool move(const room r, int x, int y);
};