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
    enum direction d;

public:
    // Costruttore
    Bullet(coords pos, int damage, direction direction = NULLO);

    int get_direction();
    void set_direction(enum direction direction);
};