#include "Hostile.hpp"

Hostile::Hostile(
    coords pos,
    char display,
    char description[],
    char name[10], int health,
    int damage, int trigger_radius) : Entity(pos, display, description, name, health, damage)
{
    this->trigger_radius = trigger_radius;
}

int Hostile::get_trigger_radius() { return this->trigger_radius; }