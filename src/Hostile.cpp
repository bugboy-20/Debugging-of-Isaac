#include "Hostile.hpp"

Hostile::Hostile(
    int trigger_radius,
    char name[10],
    int health,
    int damage,
    coords pos,
    char display,
    char description[]) : Entity(name, health, damage, pos, display, description)
{
    this->trigger_radius=trigger_radius;
    this->health=health;
    this->damage=damage;
};



int Hostile::get_trigger_radius() {
    return this->trigger_radius;
}
