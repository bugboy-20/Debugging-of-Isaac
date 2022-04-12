#pragma once
#include "Weapon.hpp"

class Ranged
{
protected:
int damage, cooldown;
public:
    Ranged(int id,int damage,int cooldown);
};
