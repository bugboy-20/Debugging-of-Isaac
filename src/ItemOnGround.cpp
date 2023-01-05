#include "ItemOnGround.hpp"

ItemOnGround::ItemOnGround(coords pos, char display, const char description[], Item *i) : Core(pos, display, description, true)
{
    this->item = i;
};

ItemOnGround::ItemOnGround(coords pos, Item *i) : ItemOnGround(pos, i->get_display(), i->get_description(), i){};

Item *ItemOnGround::get_item() { return this->item; }