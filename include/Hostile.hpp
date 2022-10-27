#pragma once

#include "Entity.hpp"

class Hostile : public Entity
{
protected:
    int trigger_radius;

public:
    Hostile(coords pos, char display, char description[], char name[10], int health, int damage, int trigger_radius);

    int get_trigger_radius();
};
