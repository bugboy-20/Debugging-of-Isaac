#include "Player.hpp"
#include "Events.hpp"
#include "constants.h"
#include "Room.hpp"
#include <cstddef>

Player::Player(coords pos) : Player(pos, player_display) {}

Player::Player(
    coords pos,
    char display) : Entity(pos, display, player_s, {player_damage, player_health, player_as, player_ms, player_range})
{
    this->inv = {{}, 0, Potion(lvl1, 10), Key(1)};
    for (int i = 0; i < player_inventory_slots; i++)
        this->inv.items[i] = NULL;

    this->max_health = player_health;
    this->score = 0;
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

void Player::set_score(int score)
{
    this->score += score;
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
    int slot = 0;
    while (inv.items[slot] != NULL)
        slot += 1;

    add_item(slot, i);
}

Item *Player::remove_item(int slot)
{
    if (inv.items[slot] == NULL)
        return NULL;
    this->inv.item_n -= 1;
    Item *temp = inv.items[slot];
    inv.items[slot] = NULL;
    add_stats(temp->get_stats(true));
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

void Player::add_potion(Room *r, Potion *p)
{
    int lvl = p->get_level();
    if (lvl > this->inv.pots.get_level())
        inv.pots.set_level(lvl);
    inv.pots.add_utilizzi(p->get_n_utilizzi());
    delete p;
    r->add_event(new InventoryChangedE());
}

void Player::use_potion(Room *room)
{
    if (health == max_health)
        return;
    int cura = this->inv.pots.use();
    change_health(cura);
    room->add_event(new PlayerHealthChangedE(this));
    room->add_event(new InventoryChangedE());
}

void Player::add_key(Room *r, Key *key)
{
    this->inv.keys.add_utilizzi(key->get_n_utilizzi());
    delete key;
    r->add_event(new InventoryChangedE());
}

bool Player::use_key(Room *room)
{
    bool used = this->inv.keys.use();
    if (used)
        room->add_event(new InventoryChangedE());
    return used;
}
void Player::add_stats(stats s)
{
    this->damage += s.damage;
    this->health += s.health;
    this->max_health += s.health;
    this->attack_speed /= s.attack_speed;
    this->movement_speed /= s.movement_speed;
    this->range += s.range;
}