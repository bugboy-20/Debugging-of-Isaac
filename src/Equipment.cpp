#include "Equipment.hpp"
#include <cstring>

Item::Item(int id, char display, char desc[], int level)
{
    this->id = id;
    this->display = display;
    strcpy(this->description, desc);
    this->level = level;
    this->item_stats = {0, 0, 0, 0, 0};
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
stats Item::get_stats(bool negate)
{
    stats s = item_stats;
    if (negate)
    {
        s.damage *= -1;
        s.health *= -1;
        s.attack_speed *= -1;
        s.movement_speed *= -1;
        s.range *= -1;
    }

    return s;
}

/* ipotesi per id:
1- consumabile
2- armatura
3- spada a bersaglio singolo
4- spada aoe
5- pistola (richiede ammo)
6- Bacca magica (no ammo)
*/

Consumable::Consumable(int id, char display, char desc[], int n) : Item(id, display, desc)
{
    n_utilizzi = n;
}
void Consumable::set_level(int lvl) { this->level = lvl; }
int Consumable::get_n_utilizzi() { return this->n_utilizzi; }
void Consumable::set_n_utilizzi(int n) { this->n_utilizzi = n; }
void Consumable::add_utilizzi(int n) { this->n_utilizzi += n; }
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

Weapon::Weapon(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->item_stats.damage = weapon_damage + (level - 1) * 2;
}
int Weapon::get_damage() { return this->item_stats.damage; }

Armor::Armor(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->item_stats.health = armor_health + (level - 1) * 3;
}
int Armor::get_health() { return this->item_stats.health; }

Boots::Boots(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->item_stats.movement_speed = -1 * boots_speed + (level - 1) * 30; // è negativo perchè the lower the better
}
int Boots::get_move_speed() { return this->item_stats.movement_speed; }

Crosshair::Crosshair(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->item_stats.range = crosshair_range + (level - 1) * 15;
}
int Crosshair::get_range() { return this->item_stats.range; }

Booster::Booster(int id, char display, char desc[], int level) : Item(id, display, desc, level)
{
    this->item_stats.attack_speed = -1 * booster_speed + (level - 1) * 90; // the lower the better
}
int Booster::get_attack_speed() { return this->item_stats.attack_speed; }