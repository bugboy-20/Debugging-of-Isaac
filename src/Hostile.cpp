#include "Hostile.hpp"

Hostile::Hostile(
    int trigger_radius,
    char name[10],
    int health,
    int damage,
    coords pos,
    char display) : Entity(name, health, damage, pos, display)
{
    this->trigger_radius=trigger_radius;
    this->health=health;
    this->damage=damage;
};