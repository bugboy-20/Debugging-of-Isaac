#include "Wall.hpp"
#include "Core.hpp"
#include "geometry.h"
Wall::Wall(line l, char display) : Core(l.p_iniziale, display) {
    this->line_lenght=l.lengh;
    this->vertical=l.vertical;
}

bool Wall::is_wall(coords p) {
    if (
        vertical
        && p.x == pos.x
        && pos.y <= p.y && p.y <= (pos.y + line_lenght)
        ) return true;
    else if (
        !vertical
        && p.y == pos.y
        && pos.x <= p.x && p.x <= (pos.x + line_lenght)
            ) return true;
    else return false;
}
