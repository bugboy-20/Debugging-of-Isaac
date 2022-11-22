#include "Entity.hpp"
#include "Events.hpp"
#include "geometry.h"
#include "physics.h"
#include <cstring>
#include <iostream>

Entity::Entity(coords pos, char display, char description[], char name[10], stats s) : Core(pos, display, description)
{
    strcpy(this->name, name);
    this->health = s.health;
    this->damage = s.damage;

    this->attack_speed = s.attack_speed; // 1 secondo
    time_now(this->last_shot);
    this->last_shot.tv_sec -= (attack_speed / 1000) + 1; // faccio in modo che per il primo controllo sia sempre

    this->movement_speed = s.movement_speed;
    time_now(this->last_move);
    this->last_move.tv_sec -= (movement_speed / 1000) + 1; // stessa cosa di sopra

    this->range = s.range;
}

bool Entity::move_up(Room *room) { return move(room, 0, -1); }
bool Entity::move_down(Room *room) { return move(room, 0, 1); }
bool Entity::move_left(Room *room) { return move(room, -1, 0); }
bool Entity::move_right(Room *Room) { return move(Room, 1, 0); }

bool Entity::move(Room *r, int x, int y)
{
    coords n_pos = {this->pos.x + x, this->pos.y + y};
    timeval now;
    time_now(now);
    // se non posso muovermi termino e ritorno che non ho avuto collisione
    if (time_elapsed(last_move, now) < movement_speed)
        return true;
    // se posso muovermi controllo se collido con qualcosa
    if (!collision(this->pos.x + x, this->pos.y + y, *r))
    {
        r->add_event(new EntityMoveE(pos, n_pos, this->get_display()));
        this->pos.x += x;
        this->pos.y += y;
        this->last_move = now;
        return true;
    }
    else
        return false;
}

void Entity::reposition(coords p) { this->pos = p; }

void Entity::action(){};
int Entity::get_damage() { return damage; }
int Entity::get_health() { return this->health; }
void Entity::set_health(int health) { this->health = health; }
void Entity::change_health(int h) { this->health += h; }

char *Entity::get_name()
{
    char *nome = new char[10];
    strcpy(nome, name);
    return nome;
}
void Entity::get_name(char n[10]) { strcpy(n, this->name); }

timeval Entity::get_last_shot() { return this->last_shot; }
void Entity::set_last_shot(timeval ls) { this->last_shot = ls; }

int Entity::get_attack_speed() { return this->attack_speed; }
void Entity::set_attack_speed(int as) { this->attack_speed = as; }

timeval Entity::get_last_move() { return this->last_move; }
void Entity::set_last_move(timeval lm) { this->last_move = lm; }

int Entity::get_movement_speed() { return this->movement_speed; }
void Entity::set_movement_speed(int ms) { this->movement_speed = ms; }