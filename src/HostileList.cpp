#include "HostileList.hpp"
#include "constants.h"

// concatena i due elementi in input mettendo il simbolo _ in mezzo
#define mc(n, c) n##_##c

#define mob(name)                              \
    char name##_string[STR_LENGTH] = name##_s; \
    name::name(coords pos, int level) : Hostile(pos, mc(name, display), mc(name, string), mc(name, string), {mc(name, damage), mc(name, health), mc(name, as), mc(name, ms), mc(name, range)}, mc(name, tr), mc(name, sm)) {}

mob(Zombie);
mob(Scheletro);
mob(Goblin);
mob(Fantasma);
mob(Slime);

// Hostile che implementano i livelli

#undef mob
#define mob(name)                              \
    char name##_string[STR_LENGTH] = name##_s; \
    name::name(coords pos, int level) : Hostile(pos, mc(name, display), mc(name, string), mc(name, string), {mc(name, damage), mc(name, health), mc(name, as), mc(name, ms), mc(name, range)}, mc(name, tr), level, mc(name, hs), mc(name, ds)) {}

/*


char zombie_string[STR_LENGTH] = zombie_s;
Zombie::Zombie(coords pos, int livello) : Hostile(pos,
                                     zombie_display,
                                     zombie_string,
                                     zombie_string,
                                     zombie_health,
                                     zombie_damage,
                                     zombie_tr) {}

char scheletro_string[STR_LENGTH] = scheletro_s;
Scheletro::Scheletro(coords pos) : Hostile(
                                       pos,
                                       scheletro_display,
                                       scheletro_string,
                                       scheletro_string,
                                       scheletro_health,
                                       scheletro_damage,
                                       scheletro_tr) {}

char goblin_string[STR_LENGTH] = goblin_s;
Goblin::Goblin(coords pos) : Hostile(
                                 pos,
                                 goblin_display,
                                 goblin_string,
                                 goblin_string,
                                 goblin_health,
                                 goblin_damage,
                                 goblin_tr) {}

char fantasma_string[STR_LENGTH] = fantasma_s;
Fantasma::Fantasma(coords pos) : Hostile(
                                     pos,
                                     fantasma_display,
                                     fantasma_string,
                                     fantasma_string,
                                     fantasma_health,
                                     fantasma_damage,
                                     fantasma_tr) {}

char slime_string[STR_LENGTH] = slime_s;
Slime::Slime(coords pos) : Hostile(
                               pos,
                               slime_display,
                               slime_string,
                               slime_string,
                               slime_health,
                               slime_damage,
                               slime_tr) {}
                               */
