#pragma once
#include "Entity.hpp"
#include "Equipment.hpp"

class Hostile : public Entity
{
protected:
    int trigger_radius;
    int health_scaling;
    int damage_scaling;
    int smartness;
    Item *drop;

public:
    Hostile(coords pos, char display, char description[], char name[10], stats, int trigger_radius, int smartness, int level, int health_scaling, int damage_scaling, Item * = NULL);
    Hostile(coords pos, char display, char description[], char name[10], stats, int trigger_radius, int smartness, Item * = NULL); // used for non scaling mob.

    int get_trigger_radius();
    int get_smartness();
    Item *get_drop();
};
