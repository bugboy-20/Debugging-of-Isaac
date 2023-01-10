#pragma once
#include "constants.h"

enum item_id
{
    item,
    potions,
    keys
};

class Item
{
protected:
    item_id id;
    char display;
    char description[STR_LENGTH];
    int level;
    stats item_stats;

public:
    Item(item_id id, char display, const char desc[STR_LENGTH], int level = 1);

    int get_level();
    int get_id();
    char get_display();
    char *get_description();
    void get_description(char[STR_LENGTH]);
    // se il parametro è false resituisce le stats, altrimenti le restituisce negate
    stats get_stats(bool negate = false);
};

class Consumable : public Item
{
protected:
    int n_utilizzi;

public:
    Consumable(item_id id, char display, const char desc[STR_LENGTH], int level = 1, int n_utilizzi = 0);

    void set_level(int);
    int get_n_utilizzi();
    void set_n_utilizzi(int);
    void add_utilizzi(int);
    // resituisce true se il consumabile è stato usato false altrimenti
    bool use();
};

class Potion : public Consumable
{
public:
    Potion(int level = 1, int n_util = 1);
    // restituisce la quantità di vita curata
    int use();
};

class Key : public Consumable
{
public:
    Key(int n_util = 1);
};

// una Weapon è un item che aumenta il danno,
// il danno viene sommato al danno base del player
class Weapon : public Item
{
    // damage formula: base_damage+(livello-1)*2
    // in pratica ogni livello il danno aumenta di 2

public:
    Weapon(char display, const char desc[STR_LENGTH], int level = 1);

    int get_damage();
};

// una Armor è un item che aumenta la vita massima
// la vita viene sommata alla vita massima del player
class Armor : public Item
{
    // health formula: base_health+(livello-1)*3
    // in pratica ogni livello la vita aumenta di 3

public:
    Armor(char display, const char desc[STR_LENGTH], int level = 1);

    int get_health();
};

// un Boots è un item che aumenta la velocità di movimento
class Boots : public Item
{
    // il cooldown di movimento viene diviso per il valore della statistica
    // base_speed + (livello-1)
    // ogni livello la move speed dell'item aumenta di 1
public:
    Boots(char display, const char desc[STR_LENGTH], int level = 1);

    double get_move_speed();
};

// un Crosshair è un item che aumenta il range
class Crosshair : public Item
{
    // range formula: base_range + (level-1)*15
    // ogni livello aumenta di 15
public:
    Crosshair(char display, const char desc[STR_LENGTH], int level = 1);

    int get_range();
};

// un Booster è un item che aumenta la velocità di attacco
class Booster : public Item
{
    // il cooldown di attacco viene diviso per il valore della statistica
    // base_attack_speed + (level-1)*0.5
    // ogni livello aumenta di 0.5
public:
    Booster(char display, const char desc[STR_LENGTH], int level = 1);

    double get_attack_speed();
};