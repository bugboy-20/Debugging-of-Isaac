#pragma once
#include "Entity.hpp"
#include "Equipment.hpp"
#include "geometry.h"

struct inventory
{
    Weapon *arma;
    Armor *armatura;
    Item *items[player_inventory_slots];
    int item_n;
};

class Player : public Entity
{
protected:
    int max_health;
    int score;
    int ammo;
    inventory inv;

public:
    Player(coords pos, char name[10], int max_health);
    Player(coords pos, char name[10], int max_health, class Weapon *w, class Armor *a);
    Player(coords pos, char display, char description[], char name[10], int damage, int max_health, int ammo, class Weapon *w, class Armor *a);
    int get_max_health();
    int get_score();

    inventory get_inventory();
    void add_item(int slot, Item *);
};
