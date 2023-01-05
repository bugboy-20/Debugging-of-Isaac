#include "Hostile.hpp"

Hostile::Hostile(coords pos,
                 char display,
                 const char description[STR_LENGTH],
                 stats s,
                 int trigger_radius,
                 int smartness,
                 int level,
                 int health_scaling,
                 int damage_scaling, Item *d) : Entity(pos, display, description, s)
{
    this->smartness = smartness;
    this->health += level * health_scaling;
    this->damage += level * damage_scaling;
    this->trigger_radius = trigger_radius;
    this->drop = d;
}

Hostile::Hostile(
    coords pos,
    char display,
    const char description[STR_LENGTH],
    stats s,
    int trigger_radius,
    int smartness, Item *d) : Hostile(pos, display, description, s, trigger_radius, smartness, 0, 0, 0, d) {}

int Hostile::get_trigger_radius() { return this->trigger_radius; }
int Hostile::get_smartness() { return this->smartness; }
Item *Hostile::get_drop()
{
    Item *i = this->drop;
    this->drop = NULL;
    return i;
}
