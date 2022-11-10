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

Consumable::Consumable(int id, char display, char desc[]) : Item(id, display, desc)
{
    n_utilizzi = 0;
}
int Consumable::get_n_utilizzi() { return this->n_utilizzi; }
void Consumable::set_n_utilizzi(int n) { this->n_utilizzi = n_utilizzi; }
void Consumable::use() { n_utilizzi -= 1; }

Potion::Potion() : Consumable(potions, '+', "pozione")
{
    livello = 1;
}
int Potion::use()
{
    Consumable::use();
    int heal = livello * 1.5;
    return heal;
}

Key::Key() : Consumable(keys, 'k', "chiave")
{
}

Weapon::Weapon(int id, char display, char desc[], int damage) : Item(id, display, desc)
{
    this->damage = damage;
}

Armor::Armor(int id, char display, char desc[], int health) : Item(id, display, desc)
{
    this->health = health;
}