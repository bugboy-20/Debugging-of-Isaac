#pragma once
#include "Entity.hpp"

class Player: public Entity{
    protected:
    Sword* spada;
    Armor* armatura;
    public:
    player(Sword s,Armor a){
        s=NULL;
        a=NULL;

    }
};