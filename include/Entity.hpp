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
    timeval last_move;
    int movement_speed;
    int range;

public:
    Entity(coords pos, char display, char description[], char name[10], stats);
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
    // somma il paramentro alla vita attuale
    void change_health(int h);
    int get_attack_speed();
    void set_attack_speed(int as);
    timeval get_last_shot();
    void set_last_shot(timeval ls);
    int get_movement_speed();
    void set_movement_speed(int ms);
    timeval get_last_move();
    void set_last_move(timeval lm);
    int get_damage();

private:
    // restituisce true se non ha fatto collsione
    bool move(Room *r, int x, int y);
};
