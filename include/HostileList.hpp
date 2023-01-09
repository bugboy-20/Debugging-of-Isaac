#pragma once
#include "Hostile.hpp"

#define mob(name)                                    \
    class name : public Hostile                      \
    {                                                \
    public:                                          \
        name(coords, int level = 0, Item *i = NULL); \
    }

mob(Zombie);
mob(Scheletro);
mob(Goblin);
mob(Fantasma);
mob(Ragno);
mob(Mummia);
mob(Vampiro);

// TODO implementare due boss
// nemici particolarmente forti senza scaling, tanta vita
mob(Golem);
mob(Mago);
mob(Drago);

#undef mob