#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Sword.hpp"

class Player : public Entity
{
protected:
    int ammo;
    int max_health;
    class Sword *spada;
    class Armor *armatura;

public:
    Player(int ammo,int max_health,class Sword *s, class Armor *a, char name[10], int health, int damage, coords pos, char display);
};