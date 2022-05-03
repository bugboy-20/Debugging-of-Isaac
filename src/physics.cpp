#include "physics.h"

bool collision(int x, int y, Room r)
{

    door_collision(x, y, r);

}

bool door_collision(int x, int y, Room r){
    if(y < 1) return true;
    else if(x < 1) return true;
    else if(y > ROOM_HEIGHT - 2) return true;
    else if( x > ROOM_WIDTH - 2) return true;
    else return false;
}

void do_room(Room *r){}; // fa cose sulla stanza

bool game_over()
{
    return false;
}