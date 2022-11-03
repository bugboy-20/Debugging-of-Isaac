#pragma once
#include "Player.hpp"
#include "Room.hpp"
#include "Bullet.hpp"
#include "Hostile.hpp"


bool collision(int x, int y, Room& r);

bool player_in_door(int x, int y, Room& r);

bool wall_collision(coords pos, Room& r);

bool general_collision(coords pos, Room& r);

void door_collision(coords pos, Room& r);

bool next_room_position(Room& r, enum door_pos p);

void repos_player_in_new_room(coords pos, Room& r, enum door_pos p, enum door_pos p1);

void shoot(Room& r, Bullet *b);

void destroy_bullet(Room& r, Bullet *b);

bool enemy_in_range(Room& r, Hostile *e);

void shoot_in_direction(Room& r, Bullet *b);

enum direction enemy_shot_direction(Room& r, Hostile *e);

void bullet_creation(Entity *e, int direction);

void enemy_range(Room& r);

void do_room(Room *r); // fa cose sulla stanza

bool game_over(Player p);
