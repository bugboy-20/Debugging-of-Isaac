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
  bool move_up(Room room);
  bool move_down(Room room);
  bool move_left(Room room);
  bool move_right(Room room);
  void action();

  char* get_name();
  int get_health();
  int get_damage();
private:
  bool move(const Room r, int x, int y);
};