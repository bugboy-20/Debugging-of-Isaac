#pragma once
#include "Core.hpp"
#include "time_handle.h"

class Room;

class Entity : public Core
{
protected:
    char name[10];
    int health;
    int damage;
    int attack_speed; // tempo in millisecondi
    timeval last_shot;

public:
    Entity(coords pos, char display, char description[], char name[10], int health, int damage);
    bool move_up(Room *room);
    bool move_down(Room *room);
    bool move_left(Room *room);
    bool move_right(Room *room);

    /* riposiziona l'entità alle cordinate specificate
    utile per quando cambia stanza
    possibile fonte di glitch */
    void reposition(coords);
    /*virtual*/ void action();

    char *get_name();
    void get_name(char[10]);
    int get_health();
    void set_health(int health);
    int get_attack_speed();
    void set_attack_speed(int as);
    timeval get_last_shot();
    void set_last_shot(timeval ls);
    int get_damage();

private:
    bool move(Room *r, int x, int y);
};
