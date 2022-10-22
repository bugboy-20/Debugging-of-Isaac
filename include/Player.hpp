#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "geometry.h"

class Player : public Entity
{
protected:
    int ammo;
    int max_health;
    class Weapon *arma;
    class Armor *armatura;
    int score;

public:
    Player(int ammo, int max_health, class Weapon *w, class Armor *a, char name[10], int damage, coords pos, char display, char description[]);
    int get_max_health();
    int get_score();

    // riposiziona il player alle cordinate specificate
    //  utile per quando cambia stanza
    //  possibile fonte di glitch
    void reposition(coords);
};
