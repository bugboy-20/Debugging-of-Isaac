#pragma once
#include "Core.hpp"
#include "Room.hpp"

class Bullet : public Core
{
    

public:
    //Costruttore
    Bullet(coords pos, char display, char description[]);

    //Metodo setter per x
    void set_x(int x);

    //Metodo setter per y
    void set_y(int y);

    //Gestisce il movimento del proiettile restituendo True in caso di collisione, False altrimenti
    bool shoot(Room *r, int x, int y);
    
};