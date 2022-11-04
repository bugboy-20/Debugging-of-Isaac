#pragma once
#include "Hostile.hpp"

#define mob(name) class name : public Hostile { \
    public: \
            name (coords); \
}

mob(Zombie);
mob(Scheletro);
mob(Goblin);
mob(Fantasma);
mob(Slime);
/*
class Zombie : public Hostile
{
public:
    Zombie(coords pos, int livello);
};

class Scheletro : public Hostile
{
public:
    Scheletro(coords pos);
};

class Goblin : public Hostile
{
public:
    Goblin(coords pos);
};

class Fantasma : public Hostile
{
public:
    Fantasma(coords pos);
};

class Slime : public Hostile
{
public:
    Slime(coords pos);
};

*/
#undef mob
