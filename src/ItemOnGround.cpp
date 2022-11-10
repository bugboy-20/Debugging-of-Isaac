#include "ItemOnGround.hpp"

ItemOnGround::ItemOnGround(coords pos, char display, char description[], Item *i) : Core(pos, display, description)
{
    this->item = i;
};

ItemOnGround::ItemOnGround(coords pos, Item *i) : Core(pos, i->display, i->description)
{
    this->item = i;
};