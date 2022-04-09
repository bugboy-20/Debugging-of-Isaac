#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Sword.hpp"

class Player : public Entity
{
protected:
    class Sword *spada;
    class Armor *armatura;

public:
    Player(class Sword *s, class Armor *a, char name[10], int health, int damage, coords pos, char display);
};