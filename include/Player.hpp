#pragma once
#include "Entity.hpp"

class Player: public Entity{
    protected:
    Sword* spada;
    Armor* armatura;
    public:
    player(this->spada,this->armatura){
        spada=NULL;
        armatura=NULL;

    }
};