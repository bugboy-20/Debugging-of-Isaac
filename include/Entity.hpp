#pragma once

#include "Core.hpp"

struct room;

class Entity : public Core
{

protected:
  char name[10];
  int health;
  int damage;

public:
  Entity(char name[10], int health, int damage, coords pos, char display);
  bool move_up(room room);
  bool move_down(room room);
  bool move_left(room room);
  bool move_right(room room);
  void action();

private:
  bool move(const room r, int x, int y);
};