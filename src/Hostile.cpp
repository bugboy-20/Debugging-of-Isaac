#include "Hostile.hpp"

Hostile::Hostile(coords pos,
                 char display,
                 char description[],
                 char name[10],
                 stats s,
                 int trigger_radius,
                 int level,
                 int smartness,
                 int health_scaling,
                 int damage_scaling) : Entity(pos, display, description, name, s)
{
    this->smartness = smartness;
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
    int trigger_radius,
    int smartness) : Hostile(pos, display, description, name, s, trigger_radius, 0, 0, 0, smartness) {
        this->smartness = smartness;
    }

int Hostile::get_trigger_radius() { return this->trigger_radius; }
int Hostile::get_smartness() { return this->smartness; }
