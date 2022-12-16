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
    Bullet(coords pos, int damage, direction direction, int range = 10000);

    int get_direction();
    void set_direction(enum direction direction);
    bool move(Room *r, int x, int y);
    bool move_up(Room *room);
    bool move_down(Room *room);
    bool move_left(Room *room);
    bool move_right(Room *room);
};