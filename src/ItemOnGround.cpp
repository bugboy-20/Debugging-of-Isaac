#include "ItemOnGround.hpp"

ItemOnGround::ItemOnGround(coords pos, char display, char description[], Item *i) : Core(pos, display, description, true)
{
    this->item = i;
};

ItemOnGround::ItemOnGround(coords pos, Item *i) : Core(pos, i->get_display(), i->get_description())
{
    this->item = i;
};