#pragma once

#include "Entity.hpp"

class Hostile : public Entity
{
protected:
    int trigger_radius;
    int health_scaling;
    int damage_scaling;

public:
    Hostile(coords pos, char display, char description[], char name[10], int health, int damage, int trigger_radius, int level, int health_scaling, int damage_scaling);
    Hostile(coords pos, char display, char description[], char name[10], int health, int damage, int trigger_radius); // used for non scaling mob.

    int get_trigger_radius();
};
