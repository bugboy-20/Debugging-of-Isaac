#pragma once
#include "Entity.hpp"
#include "Room.hpp"
using namespace std::chrono::_V2;

class Bullet : public Entity
{
protected:
    system_clock::time_point last_move;
    int movement_speed;
    int direction;

public:
    // Costruttore
    Bullet(coords pos, int damage);

    int get_movement_speed();
    void set_movement_speed(int ms);
    system_clock::time_point get_last_move();
    void set_last_move(system_clock::time_point lm);
    int get_direction();
    void set_direction(int direction);
};