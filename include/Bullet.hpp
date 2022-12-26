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

    move_outcome move(Room *r, int x, int y);

public:
    Bullet(coords pos, int damage, direction direction, int range);

    int get_direction();
    void set_direction(enum direction direction);
    move_outcome move_up(Room *room);
    move_outcome move_down(Room *room);
    move_outcome move_left(Room *room);
    move_outcome move_right(Room *room);
};