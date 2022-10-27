#pragma once
#include "Entity.hpp"
#include "Equipment.hpp"
#include "geometry.h"

class Player : public Entity
{
protected:
    int max_health;
    int score;
    int ammo;
    class Weapon *arma;
    class Armor *armatura;

public:
    Player(coords pos, char name[10], int max_health, class Weapon *w, class Armor *a);
    Player(coords pos, char display, char description[], char name[10], int damage, int max_health, int ammo, class Weapon *w, class Armor *a);
    int get_max_health();
    int get_score();
};
