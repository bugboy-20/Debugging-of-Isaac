#include "Entity.hpp"

Entity::Entity(){
  health = 0;
  damage = 0;
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