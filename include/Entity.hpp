#pragma once

#include "Core.hpp"

struct room;

class Entity: public Core{

protected:
    char name[10];
    int health;
    int damage;

public:
    Entity(int health, int damage){ // costruttore spero
        this->health=0;
        this->damage=0;
    };
//chiede una copia della "planimetria" della stanza
//cerca di muovere l'entità, restituisce true qualora la cosa abbia sucesso
// btw se hai non hai idee su come implementare questo metodo, una proposta l'avevo scritta sul main
// collision è un metodo fatto da Saad che ritorna True quando nella posizione c'è già un oggetto incompenetrabile della stanza    
    bool move_up(room room){   
        move( const room r, int x, int y) {
            if(!collision(this->x,this->y,r)){
                this->y += 1;
                return true;
                    } else return false;
                }
    bool move_down(room room);
    bool move_left(room room);
    bool move_right(room room);
};
