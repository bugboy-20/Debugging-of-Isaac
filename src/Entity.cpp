#include "Entity.hpp"
#include "Room.h"

Entity::Entity(int health,int damage){
  health = 0;
  damage = 0;
};
  bool Entity::move_up(room room) {
    return move(room, 0, -1);
  };
  bool Entity::move_down(room room) {
    return move(room, 0, 1);
  };
  bool Entity::move_left(room room) {
    return move(room, 1, 0);
  };
  bool Entity::move_right(room room) {
    return move(room, -1, 0);
  };
bool Entity::move(const room r, int x, int y){
   if(!collision(this->pos.x+x,this->pos.y+y,r)) {
     this->pos.x += x;
     this->pos.y += y;
     return true;
  } else return false;
};