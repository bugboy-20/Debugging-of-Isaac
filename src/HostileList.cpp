#include "HostileList.hpp"
#include "constants.h"

Zombie::Zombie(coords pos) : Hostile(pos,
                                     zombie_display,
                                     zombie_desc,
                                     zombie_name,
                                     zombie_health,
                                     zombie_damage,
                                     zombie_tr) {}

Scheletro::Scheletro(coords pos) : Hostile(
                                       pos,
                                       scheletro_display,
                                       scheletro_desc,
                                       scheletro_name,
                                       scheletro_health,
                                       scheletro_damage,
                                       scheletro_tr) {}

Goblin::Goblin(coords pos) : Hostile(
                                 pos,
                                 goblin_display,
                                 goblin_desc,
                                 goblin_name,
                                 goblin_health,
                                 goblin_damage,
                                 goblin_tr) {}

Fantasma::Fantasma(coords pos) : Hostile(
                                     pos,
                                     fantasma_display,
                                     fantasma_desc,
                                     fantasma_name,
                                     fantasma_health,
                                     fantasma_damage,
                                     fantasma_tr) {}

Slime::Slime(coords pos) : Hostile(
                               pos,
                               slime_display,
                               slime_desc,
                               slime_name,
                               slime_health,
                               slime_damage,
                               slime_tr) {}