#include "Player.hpp"

Player::Player(
    class Sword *s,
    class Armor *a,
    char name[10],
    int health,
    int damage,
    coords pos,
    char display) : Entity(name, health, damage, pos, display)
{
    this->spada = s;
    this->armatura = a;
};
