#include "Player.hpp"
#include "Events.hpp"
#include "constants.h"
#include "Room.hpp"
#include <cstddef>

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
    // this->inv.pots->set_n_utilizzi(4);
    for (int i = 0; i < player_inventory_slots; i++)
        this->inv.items[i] = NULL;

    this->max_health = max_health;
    this->ammo = ammo;
    this->score = 0;

    if (a != NULL)
    {
        this->health = a->get_health() + max_health;
        this->max_health = a->get_health() + max_health;
    }
    if (w != NULL)
        this->damage = damage + w->get_damage();
}

int Player::get_max_health() { return this->max_health; }
int Player::get_score() { return this->score; }
void Player::set_health(int h)
{
    if (h > this->max_health)
        this->health = this->max_health;
    else
        this->health = h;
}

void Player::change_health(int h)
{
    if (this->health + h > this->max_health)
        this->health = this->max_health;
    else
        this->health += h;
}

inventory Player::get_inventory()
{
    return this->inv;
}

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

void Player::use_potion(Room *room)
{
    if (health == max_health) // TODO: decidere se tenere o no questa feature
        return;               // se il player è full vita non viene curato
    int cura = this->inv.pots.use();
    change_health(cura);
    room->add_event(new PlayerHealthChangedE(this));
    room->add_event(new ConsumableUsedE());
}
