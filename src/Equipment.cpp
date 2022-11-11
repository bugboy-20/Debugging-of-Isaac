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
bool Consumable::use()
{
    if (n_utilizzi <= 0)
        return false;
    n_utilizzi -= 1;
    return true;
}

Potion::Potion() : Consumable(potions, '+', "pozione")
{
    livello = 1;
    n_utilizzi = 10;
}
int Potion::use()
{
    bool is_used = Consumable::use();

    if (is_used)
        return livello * 1.5;
    return 0;
}

Key::Key() : Consumable(keys, 'k', "chiave")
{
    n_utilizzi = 0;
}

Weapon::Weapon(int id, char display, char desc[], int damage) : Item(id, display, desc)
{
    this->damage = damage;
}

Armor::Armor(int id, char display, char desc[], int health) : Item(id, display, desc)
{
    this->health = health;
}