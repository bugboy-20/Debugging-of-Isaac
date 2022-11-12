#include "Equipment.hpp"
#include <cstring>

Item::Item(int id, char display, char desc[])
{
    this->id = id;
    this->display = display;
    strcpy(this->description, desc);
    this->level = 1;
}
Item::Item(int id, char display, char desc[], int level) : Item(id, display, desc)
{
    this->level = level;
}

int Item::get_level() { return this->level; }
int Item::get_id() { return this->id; }
char Item::get_display() { return this->display; }

char *Item::get_description()
{
    char *desc = new char[STR_LENGTH];
    strcpy(desc, this->description);
    return desc;
}
void Item::get_description(char d[STR_LENGTH]) { strcpy(d, this->description); }

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

char potion_desc[STR_LENGTH] = potion_d;
Potion::Potion() : Consumable(potions, '+', potion_desc)
{
    level = 1;
    n_utilizzi = 10;
}
int Potion::use()
{
    bool is_used = Consumable::use();

    if (is_used)
        return level * 1.5;
    return 0;
}

char key_desc[STR_LENGTH] = key_d;
Key::Key() : Consumable(keys, 'k', key_desc)
{
    n_utilizzi = 0;
}

Weapon::Weapon(int id, char display, char desc[]) : Weapon(id, display, desc, 1) {}

Weapon::Weapon(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->damage = weapon_damage + (level - 1) * 2;
}

int Weapon::get_damage() { return this->damage; }

Armor::Armor(int id, char display, char desc[]) : Armor(id, display, desc, 1) {}

Armor::Armor(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->health = armor_health + (level - 1) * 3;
}

int Armor::get_health() { return this->health; }