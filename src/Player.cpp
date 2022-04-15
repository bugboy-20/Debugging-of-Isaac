#include "Player.hpp"

Player::Player(
    int max_health,
    int ammo,
    class Weapon *w,
    class Armor *a,
    char name[10],
    int health,
    int damage,
    coords pos,
    char display) : Entity(name, health, damage, pos, display)
{
    this->arma = w;
    this->armatura = a;
};
