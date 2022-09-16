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
    char display,
    char description[]) : Entity(name, health, damage, pos, display, description)
{
    this->arma = w;
    this->armatura = a;
    this->max_health=max_health;
    this->ammo =ammo;
    this->score = 0;
};

int Player::get_max_health() {
    return this->max_health;
}
