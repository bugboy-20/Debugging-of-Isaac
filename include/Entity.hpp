#pragma once

#include "Core.hpp"

struct room;

class Entity: public Core {

    protected: char name[10];
    int health;
    int damage;

    public: Entity(int health, int damage) { // costruttore spero
      this -> health = 0;
      this -> damage = 0;
      bool move_up(room room) {
        return move(room, 0, -1);
      };
      bool move_down(room room) {
        return move(room, 0, 1);
      };
      bool move_left(room room) {
        return move(room, 1, 0);
      };
      bool move_right(room room) {
        return move(room, -1, 0);
      };
    };
    private: bool move(const room r, int x, int y) {
      if (!collision(this -> pos.x + x, this -> pos.y + y, r)) {
        this -> pos.x += x;
        this -> pos.y += y;
        return true;
      } else return false;
    }