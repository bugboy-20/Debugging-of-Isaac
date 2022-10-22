#include "Player.hpp"
#include "geometry.h"

Player::Player(
    int ammo,
    int max_health,
    class Weapon *w, 
    class Armor *a,
    char name[10],
    int damage,
    coords pos, 
    char display, 
    char description[]) : Entity(name, max_health, damage, pos, display, description)
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
int Player::get_score(){
    return this->score;
}

void Player::reposition(coords p) {
    this->pos=p;
}
