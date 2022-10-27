#include "Entity.hpp"
#include "Entity.hpp"
#include "Events.hpp"
#include "geometry.h"
#include "physics.h"
#include <cstring>

Entity::Entity(coords pos, char display, char description[], char name[10], int health, int damage) : Core(pos, display, description)
{
    strcpy(this->name, name);
    this->health = health;
    this->damage = damage;
}

bool Entity::move_up(Room *room) { return move(room, 0, -1); }
bool Entity::move_down(Room *room) { return move(room, 0, 1); }
bool Entity::move_left(Room *room) { return move(room, -1, 0); }
bool Entity::move_right(Room *Room) { return move(Room, 1, 0); }

bool Entity::move(Room *r, int x, int y)
{
    coords n_pos = {this->pos.x + x, this->pos.y + y};

    if (!collision(this->pos.x + x, this->pos.y + y, *r))
    {
        r->add_event(new EntityMoveE(pos, n_pos, this->get_display()));
        this->pos.x += x;
        this->pos.y += y;
        return true;
    }
    else
        return false;
}

void Entity::reposition(coords p) { this->pos = p; }

void Entity::action(){};
int Entity::get_damage() { return damage; };
int Entity::get_health() { return this->health; };
void Entity::set_health(int health) { this->health = health; }
char *Entity::get_name()
{
    char *nome = new char[10];
    strcpy(nome, name);
    return nome;
};
void Entity::get_name(char n[10]) { strcpy(n, this->name); }
