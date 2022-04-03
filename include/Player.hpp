#pragma once
#include "Entity.hpp"

class Player: public Entity{
    protected:
    Sword*;
    Armor*;
    public:
    player(this->Sword,this->Armor){
        Sword=NULL;
        Armor=NULL;

    }
};
