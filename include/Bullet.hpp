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
    int space_travelled;

public:
    // di default ha range infinito
    Bullet(coords pos, int damage, direction direction = NULLO, int range = 100000);

    int get_direction();
    void set_direction(enum direction direction);
};