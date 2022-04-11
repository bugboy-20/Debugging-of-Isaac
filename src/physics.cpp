#include "physics.h"

bool collision(int x, int y, room r)
{

    if(y < 1) return true;
    else if(x < 1) return true;
    else if(y > ROOM_HEIGHT - 2) return true;
    else if( x > ROOM_WIDTH - 2) return true;
    else return false;

}

void do_room(room *r){}; // fa cose sulla stanza

bool game_over()
{
    return false;
}