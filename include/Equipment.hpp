#pragma once
#include "constants.h"

enum item_id
{
    weapon,
    armor,
    consumable
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
public:
    Consumable(int id, char display, char desc[]);
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