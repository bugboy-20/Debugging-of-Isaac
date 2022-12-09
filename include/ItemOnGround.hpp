#pragma once
#include "Core.hpp"
#include "Equipment.hpp"

class ItemOnGround : public Core
{
protected:
    Item *item;

public:
    ItemOnGround(coords pos, Item *);
    ItemOnGround(coords pos, char display, char description[], Item *);
    Item* get_item();
};
