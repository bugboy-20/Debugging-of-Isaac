#pragma once
#include "Core.hpp"
#include "time_handle.h"

class Room;
enum move_outcome
{
    COLLISION,
    MOVEMENT,
    TIMEOUT
};

class Entity : public Core
{
protected:
    int health;
    int damage;
    int attack_speed; // tempo in millisecondi
    timeval last_shot;
    timeval last_move;
    int movement_speed;
    int range;

    /**
     * restituisce COLLISION se ha provato a muoversi in un pixel occupato,
     * MOVEMENT se si è mosso
     * TIMEOUT se non può ancora muoversi
     */
    move_outcome move(Room *r, int x, int y);

public:
    Entity(coords pos, char display, const char description[STR_LENGTH], stats);
    move_outcome move_up(Room *room);
    move_outcome move_down(Room *room);
    move_outcome move_left(Room *room);
    move_outcome move_right(Room *room);

    /* riposiziona l'entità alle cordinate specificate
    utile per quando cambia stanza
    possibile fonte di glitch */
    void reposition(coords);
    /*virtual*/ void action();

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
    int get_range();
};
