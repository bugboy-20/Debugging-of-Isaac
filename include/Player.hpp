#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Spada.hpp"

class Player: public Entity{
    protected:
    Sword* spada;
    Armor* armatura;
    public:
        Player(Sword s, Armor a);
};