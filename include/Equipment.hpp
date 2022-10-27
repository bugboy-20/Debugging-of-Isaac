#pragma once

class Inventoryable
{
protected:
    int id;

public:
    Inventoryable(int id);
};

class Consumable
{
public:
    Consumable();
};

class Weapon
{
protected:
    int damage;

public:
    Weapon(int damage);
};

class Armor
{
protected:
    int health;

public:
    Armor(int health);
};
