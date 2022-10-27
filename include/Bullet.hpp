#pragma once
#include "Entity.hpp"
#include "Room.hpp"

class Bullet : public Entity
{

public:
    // Costruttore
    Bullet(coords pos);

    // Gestisce il movimento del proiettile restituendo True in caso di collisione, False altrimenti
    bool shoot(Room *r, int x, int y);
};