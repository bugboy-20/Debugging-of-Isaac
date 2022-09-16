#include "Hostile.hpp"
#include "HostileList.hpp"

char ZombieName[10] = "Zombie";
char ZombieDesc[] = "test";
Zombie::Zombie(coords pos) : Hostile(6, ZombieName, 100, 20, pos, 'z', ZombieDesc){}