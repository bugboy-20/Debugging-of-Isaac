#pragma once
#include "Core.hpp"
class Room;

class Entity : public Core
{

protected:
  char name[10];
  int health;
  int damage;

public:
  Entity(char name[10], int health, int damage, coords pos, char display, char description[]);
  bool move_up(Room *room);
  bool move_down(Room *room);
  bool move_left(Room *room);
  bool move_right(Room *room);
  void action();

  char* get_name();
  void get_name(char[10]);
  int get_health();
  int get_damage();
private:
  bool move(Room *r, int x, int y);
};
