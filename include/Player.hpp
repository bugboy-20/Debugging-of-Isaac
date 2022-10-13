#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"

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
};