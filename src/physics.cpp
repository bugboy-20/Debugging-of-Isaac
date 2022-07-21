#include "physics.h"
#include <RoomEvent.hpp>
#include <EntityMoveE.hpp>
#include <Player.hpp>

bool collision(int x, int y, Room r)
{
    bool flag;
    
    flag = door_collision(x, y, r);

    return flag;
}

bool door_collision(int x, int y, Room r){
    if(y < 1) return true;
    else if(x < 1) return true;
    else if(y > ROOM_HEIGHT - 2) return true;
    else if( x > ROOM_WIDTH - 2) return true;
    else return false;
}

void do_room(Room *r){}; // fa cose sulla stanza

bool game_over(Player p)
{
    //il gioco termina quando finisce la vita 
    if(p.get_health()<=0) return true;
    else return false;
}