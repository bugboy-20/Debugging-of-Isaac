#include <cstddef>
#include <string.h>
#include "physics.h"
#include "Events.hpp"
#include "Hostile.hpp"
#include "Map.h"

List bullets;

bool collision(int x, int y, Room& r)
{
    bool flag1, flag2, flag3;
    coords pos;

    pos.x = x;
    pos.y = y;
    flag1 = wall_collision(pos, r);
    flag2 = general_collision(pos, r);
    door_collision(pos, r);
    if(flag1 || flag2) return true;
    else return false;
}

bool wall_collision(coords pos, Room& r)
{
    if(pos.y < 1) return true;
    else if(pos.x < 1) return true;
    else if(pos.y > ROOM_HEIGHT - 2) return true;
    else if( pos.x > ROOM_WIDTH - 2) return true;
    else return false;
}

bool general_collision(coords pos, Room& r){
    if(r.get_element_in_this_position(pos) == NULL){
        return false;
    }else{
        return true;
    }
}

void door_collision(coords pos, Room& r)
{
    if(pos.x == door_position(LEFT_DOOR)[0].x &&  pos.y == door_position(LEFT_DOOR)[0].y || 
    pos.x == door_position(LEFT_DOOR)[1].x &&  pos.y == door_position(LEFT_DOOR)[1].y){  

        if(next_room_position(r, LEFT_DOOR))  repos_player_in_new_room(pos, r, LEFT_DOOR, RIGHT_DOOR);
           
    }else if(pos.x == door_position(RIGHT_DOOR)[0].x &&  pos.y == door_position(RIGHT_DOOR)[0].y || 
    pos.x == door_position(RIGHT_DOOR)[1].x &&  pos.y == door_position(RIGHT_DOOR)[1].y){
           
        if(next_room_position(r, RIGHT_DOOR))  repos_player_in_new_room(pos, r, RIGHT_DOOR, LEFT_DOOR);

    }else if(pos.x == door_position(UPPER_DOOR)[0].x &&  pos.y == door_position(UPPER_DOOR)[0].y || 
    pos.x == door_position(UPPER_DOOR)[1].x &&  pos.y == door_position(UPPER_DOOR)[1].y){

        if(next_room_position(r, UPPER_DOOR))  repos_player_in_new_room(pos, r, UPPER_DOOR, LOWER_DOOR);

    }else if(pos.x == door_position(LOWER_DOOR)[0].x &&  pos.y == door_position(LOWER_DOOR)[0].y || 
    pos.x == door_position(LOWER_DOOR)[1].x &&  pos.y == door_position(LOWER_DOOR)[1].y){
            
        if(next_room_position(r, LOWER_DOOR))  repos_player_in_new_room(pos, r, LOWER_DOOR, UPPER_DOOR);

    }
}

void repos_player_in_new_room(coords pos, Room& r, enum door_pos p, enum door_pos p1){
    coords old_pos, new_pos;
    if(pos.x == door_position(p)[0].x &&  pos.y == door_position(p)[0].y){
        old_pos = door_position(p)[0];
        new_pos = door_position(p1)[0];
    }else{
        old_pos = door_position(p)[1];
        new_pos = door_position(p1)[1];
    }
    r.next_room(p)->p->reposition(new_pos);
    r.next_room(p)->add_event(new EntityMoveE(old_pos, new_pos, r.next_room(p)->p->get_display()));
}

bool next_room_position(Room& r, enum door_pos p){
    if(r.door[p]!=NULL) {
        if(r.door[p]->next_room != NULL){
            change_room(r.next_room(p));
        }else{
            change_room(add_room(&r, p));
        }
        bullets.destroy();
        return true;
    }else return false;
}

void do_room(Room *r){return ;}; // fa cose sulla stanza

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}
