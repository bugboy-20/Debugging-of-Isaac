#pragma once
#include "constants.h"

enum item_id
{
    weapon,
    armor,
    potions,
    keys
};

class Item
{
public:
    int id;
    char display;
    char description[STR_LENGTH];

public:
    Item();
    Item(int id, char display, char desc[]);
};

class Consumable : public Item
{
private:
    int n_utilizzi;

public:
    Consumable(int id, char display, char desc[]);

    int get_n_utilizzi();
    void set_n_utilizzi(int n);
    void use();
};

class Potion : public Consumable
{
private:
    int livello;

public:
    Potion();
    int use();
};

class Key : public Consumable
{
public:
    Key();
};

class Weapon : public Item
{
protected:
    int damage;

public:
    Weapon(int id, char display, char desc[], int damage);
};

class Armor : public Item
{
protected:
    int health;

public:
    Armor(int id, char display, char desc[], int health);
};