#include "Hostile.hpp"
#include "HostileList.hpp"

char zombie_name[10] = "Zombie";
char zombie_desc[] = "test";
Zombie::Zombie(coords pos) : Hostile(pos, 'z', zombie_desc, zombie_name, 50, 20, 6) {}