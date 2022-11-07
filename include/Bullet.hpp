#pragma once
#include "Entity.hpp"
#include "Room.hpp"
enum direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT,
    NULLO
};

class Bullet : public Entity
{
protected:
    timeval last_move;
    int movement_speed;
    enum direction d;

public:
    // Costruttore
    Bullet(coords pos, int damage);

    int get_movement_speed();
    void set_movement_speed(int ms);
    timeval get_last_move();
    void set_last_move(timeval lm);
    int get_direction();
    void set_direction(enum direction direction);
};