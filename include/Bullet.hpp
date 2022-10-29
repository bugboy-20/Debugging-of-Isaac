#pragma once
#include "Entity.hpp"
#include "Room.hpp"

class Bullet : public Entity
{

public:
    // Costruttore
    Bullet(coords pos, int damage);
};