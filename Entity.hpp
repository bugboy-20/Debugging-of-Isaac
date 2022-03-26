#include "Core.hpp"
#include "Map.h"

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

    bool move_up(room room);    //chiede una copia della "planimetria" della stanza
                                //cerca di muovere l'entità, restituisce true qualora la cosa abbia sucesso
                    // btw se hai non hai idee su come implementare questo metodo, una proposta l'avevo scritta sul main
    bool move_down(room room);
    bool move_left(room room);
    bool move_right(room room);
};
