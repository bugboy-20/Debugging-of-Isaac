#include "Equipment.hpp"
#include <cstring>

Item::Item(int id, char display, char desc[])
{
    this->id = id;
    this->display = display;
    strcpy(this->description, desc);
};
/* ipotesi per id:
1- consumabile
2- armatura
3- spada a bersaglio singolo
4- spada aoe
5- pistola (richiede ammo)
6- Bacca magica (no ammo)
*/

Consumable::Consumable(int id, char display, char desc[]) : Item(id, display, desc) {}

Weapon::Weapon(int id, char display, char desc[], int damage) : Item(id, display, desc)
{
    this->damage = damage;
}

Armor::Armor(int id, char display, char desc[], int health) : Item(id, display, desc)
{
    this->health = health;
}