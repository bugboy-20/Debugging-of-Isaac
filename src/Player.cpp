#include "Player.hpp"
#include "Events.hpp"
#include "constants.h"
#include "Room.hpp"
#include <cstddef>

char player_desc[20] = player_s;
Player::Player(
    coords pos,
    char name[10],
    int max_health) : Player(pos, player_display, player_desc, name, player_base_damage, max_health) {}

Player::Player(
    coords pos,
    char display,
    char description[20],
    char name[10],
    int damage,
    int max_health) : Entity(pos, display, description, name, max_health, damage)
{
    this->inv = {{}, 0, Potion(), Key()};
    for (int i = 0; i < player_inventory_slots; i++)
        this->inv.items[i] = NULL;

    this->max_health = max_health;
    this->score = 0;
    this->movement_speed = 250;
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
    add_stats(i->get_stats());
}

void Player::add_item(Item *i)
{
    int slot = inv.item_n;
    while (inv.items[slot] != NULL)
        slot += 1;

    add_item(slot, i);
}

Item *Player::remove_item(int slot)
{
    if (inv.items[slot] == NULL)
        return NULL;
    add_stats(inv.items[slot]->get_stats(true));
    Item *temp = inv.items[slot];
    inv.items[slot] = NULL;
    return temp;
}

Item *Player::remove_item(Item *item)
{
    int slot = -1;
    for (int i = 0; i < player_inventory_slots; i++)
        if (item == inv.items[i])
        {
            slot = i;
            break;
        }

    if (slot == -1)
        return NULL;
    return remove_item(slot);
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

void Player::add_stats(stats s)
{
    this->damage += s.damage;
    this->health += s.health;
    this->max_health += s.health;
    this->attack_speed += s.attack_speed;
}