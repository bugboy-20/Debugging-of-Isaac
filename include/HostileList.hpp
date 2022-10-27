#pragma once
#include "Hostile.hpp"

class Zombie : public Hostile
{
public:
    Zombie(coords pos);
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