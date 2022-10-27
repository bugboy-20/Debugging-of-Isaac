#include "Equipment.hpp"

Inventoryable::Inventoryable(int id)
{
    this->id = id;
};
/* ipotesi per id:
1- consumabile
2- armatura
3- spada a bersaglio singolo
4- spada aoe
5- pistola (richiede ammo)
6- Bacca magica (no ammo)
*/

Consumable::Consumable() {}

Weapon::Weapon(int damage)
{
    this->damage = damage;
}

Armor::Armor(int health)
{
    this->health = health;
}