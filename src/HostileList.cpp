#include "HostileList.hpp"
#include "constants.h"

// concatena i due elementi in input mettendo il simbolo _ in mezzo
#define mc(n, c) n##_##c

// Hostile che implementano i livelli
#define mob(name) \
    name::name(coords pos, int level, Item *i) : Hostile(pos, mc(name, display), mc(name, s), {mc(name, damage), mc(name, health), mc(name, as), mc(name, ms), mc(name, range)}, mc(name, tr), mc(name, smartness), level, mc(name, hs), mc(name, ds), i){};

mob(Zombie);
mob(Scheletro);
mob(Goblin);
mob(Fantasma);
mob(Ragno);
mob(Mummia);
mob(Vampiro);

mob(Golem);
mob(Mago);
mob(Drago);

#undef mob