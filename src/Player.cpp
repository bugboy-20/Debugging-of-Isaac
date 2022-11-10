#include "Player.hpp"
#include "constants.h"

char player_desc[20] = player_s;
Player::Player(
    coords pos,
    char name[10],
    int max_health) : Player(pos, player_display, player_desc, name, player_base_damage, max_health, player_ammo, NULL, NULL) {}

Player::Player(
    coords pos,
    char name[10],
    int max_health,
    class Weapon *w,
    class Armor *a) : Player(pos, player_display, player_desc, name, player_base_damage, max_health, player_ammo, w, a) {}

Player::Player(
    coords pos,
    char display,
    char description[20],
    char name[10],
    int damage,
    int max_health,
    int ammo,
    class Weapon *w,
    class Armor *a) : Entity(pos, display, description, name, max_health, damage)
{
    this->inv = {w, a, {}, 0, Potion(), Key()};
    for (int i = 0; i < player_inventory_slots; i++)
        this->inv.items[i] = NULL;

    this->max_health = max_health;
    this->ammo = ammo;
    this->score = 0;
}

int Player::get_max_health() { return this->max_health; }
int Player::get_score() { return this->score; }

inventory Player::get_inventory() { return this->inv; }

void Player::add_item(int slot, Item *i)
{
    if (slot >= player_inventory_slots)
        return;
    this->inv.items[slot] = i;
    this->inv.item_n += 1;
}

void Player::add_item(Item *i)
{
    int slot = inv.item_n;
    while (inv.items[slot] != NULL)
        slot += 1;

    this->inv.items[slot] = i;
    this->inv.item_n += 1;
}
