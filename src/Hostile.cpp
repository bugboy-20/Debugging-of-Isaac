#include "Hostile.hpp"

Hostile::Hostile(coords pos,
                 char display,
                 char description[],
                 char name[10],
                 stats s,
                 int trigger_radius,
                 int level,
                 int health_scaling,
                 int damage_scaling) : Entity(pos, display, description, name, s)
{
    this->health += level * health_scaling;
    this->damage += damage * damage_scaling;
    this->trigger_radius = trigger_radius;
}

Hostile::Hostile(
    coords pos,
    char display,
    char description[],
    char name[10],
    stats s,
    int trigger_radius) : Hostile(pos, display, description, name, s, trigger_radius, 0, 0, 0) {}

int Hostile::get_trigger_radius() { return this->trigger_radius; }
