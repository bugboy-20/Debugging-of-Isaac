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
    if(pos.x == 0 && pos.y == (ROOM_HEIGHT/2) || pos.x == 0 && pos.y == (ROOM_HEIGHT/2) - 1){  
        next_room_position(r, LEFT_DOOR);
    }else if(pos.x == ROOM_WIDTH-1 && pos.y == (ROOM_HEIGHT/2) || pos.x ==  ROOM_WIDTH-1 && pos.y == (ROOM_HEIGHT/2) - 1){
        next_room_position(r, RIGHT_DOOR);
    }else if(pos.x == ROOM_WIDTH/2 && pos.y == 0 || pos.x ==  (ROOM_WIDTH/2) - 1 && pos.y == 0){
        next_room_position(r, UPPER_DOOR);
    }else if(pos.x == ROOM_WIDTH/2 && pos.y == (ROOM_HEIGHT-1) || pos.x ==  (ROOM_WIDTH/2) - 1 && pos.y == (ROOM_HEIGHT-1)){
        next_room_position(r, LOWER_DOOR);
    }
}

void next_room_position(Room& r, enum door_pos p){
    if(r.next_room(p) != NULL){
        //change_room(r.next_room(p));
    }else{
        add_room(&r, p);
        //change_room(r.next_room(p));
    }
    r.add_event(new RoomChangedE());
}


void do_room(Room *r){return ;}; // fa cose sulla stanza

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}
