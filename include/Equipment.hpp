#pragma once
#include "constants.h"

enum item_id
{
    weapon,
    armor,
    potions,
    keys
};

struct stats
{
    int damage;
    int health;
    int attack_speed;
    int movement_speed;
    int range;
};

class Item
{
protected:
    int id;
    char display;
    char description[STR_LENGTH];
    int level;
    stats item_stats;

public:
    Item(int id, char display, char desc[], int level = 1);

    int get_level();
    int get_id();
    char get_display();
    char *get_description();
    void get_description(char[20]);
    // se il parametro è false resituisce le stats, altrimenti le restituisce negate
    stats get_stats(bool negate = false);
};

class Consumable : public Item
{
protected:
    int n_utilizzi;

public:
    Consumable(int id, char display, char desc[], int n_utilizzi = 0);

    int get_n_utilizzi();
    void set_n_utilizzi(int n);
    // resituisce true se il consumabile è stato usato false altrimenti
    bool use();
};

class Potion : public Consumable
{
public:
    Potion();
    // restituisce la quantità di vita curata
    int use();
};

// per ora Key è letteralmente un consumable con un altro nome,
// TODO forse è una classe da togliere?
class Key : public Consumable
{
public:
    Key();
};

// una Weapon è un item che aumenta il danno,
// il danno viene sommato al danno base del player
class Weapon : public Item
{
    // damage formula: base_damage+(livello-1)*2
    // in pratica ogni livello il danno aumenta di 2

public:
    Weapon(int id, char display, char desc[], int level = 1);

    int get_damage();
};

// una Armor è un item che aumenta la vita massima
// la vita viene sommata alla vita massima del player
class Armor : public Item
{
    // health formula: base_health+(livello-1)*3
    // in pratica ogni livello la vita aumenta di 3

public:
    Armor(int id, char display, char desc[], int level = 1);

    int get_health();
};