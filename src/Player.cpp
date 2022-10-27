#include "Player.hpp"

char player_desc[20] = "giocatore";
Player::Player(
    coords pos,
    char name[10],
    int max_health,
    class Weapon *w,
    class Armor *a) : Entity(pos, '@', player_desc, name, max_health, 3)
{
    this->arma = w;
    this->armatura = a;
    this->max_health = max_health;
    this->ammo = 40;
    this->score = 0;
}

Player::Player(
    coords pos,
    char display,
    char description[20],
    char name[10],
    int damage,
    int max_health,
    int ammo,
    class Weapon *w,
    class Armor *a) : Entity(pos, display, description, name, max_health, damage)
{
    this->arma = w;
    this->armatura = a;
    this->max_health = max_health;
    this->ammo = ammo;
    this->score = 0;
}

int Player::get_max_health() { return this->max_health; }
int Player::get_score() { return this->score; }
