#pragma once

#include "Entity.hpp"

class Hostile : public Entity
{
protected:
    int trigger_radius;

public:
    Hostile(int trigger_radius, char name[10], int health, int damage, coords pos, char display, char description[]);
};