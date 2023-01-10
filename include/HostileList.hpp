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
mob(Torretta);

// Boss
mob(Golem);
mob(Mago);
mob(Drago);

#undef mob