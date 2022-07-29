#include "physics.h"
#include <RoomEvent.hpp>
#include <EntityMoveE.hpp>
#include <Player.hpp>

bool collision(int x, int y, Room r)
{
    bool flag;
    coords pos;

    pos.x = x;
    pos.y = y;

    
    flag = door_collision(x, y, r);
    if(flag) return flag;
    flag = general_collision(pos, r);
    
    return flag;
}

bool door_collision(int x, int y, Room r){
    if(y < 1) return true;
    else if(x < 1) return true;
    else if(y > ROOM_HEIGHT - 2) return true;
    else if( x > ROOM_WIDTH - 2) return true;
    else return false;
}

bool general_collision(coords pos, Room r){
    if(r.get_element_in_this_position(pos) == NULL){
        return false;
    }else return true;
}

void do_room(Room *r){}; // fa cose sulla stanza

bool game_over(Player p)
{
    if(p.get_health()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}