using namespace std;
#include "c_core.hpp"
class c_entity: public c_core{
protected:
    char name[10];
    int health;
    int damage;
public:
    c_entity(int health, int damage){ // costruttore spero
        this->health=0;
        this->damage=0;
        };
};