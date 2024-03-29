#pragma once
#include <cstddef>
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
    Hostile(coords pos, char display, const char description[STR_LENGTH], stats, int trigger_radius, int smartness, int level, int health_scaling, int damage_scaling, Item * = NULL);
    Hostile(coords pos, char display, const char description[STR_LENGTH], stats, int trigger_radius, int smartness, Item * = NULL); // used for non scaling mob.

    int get_trigger_radius();
    int get_smartness();
    // restituisce il puntatore dell'oggetto del nemico, e successivamente lo elimina
    // dopo la prima chiamata ritorna NULL
    Item *get_drop();
};
