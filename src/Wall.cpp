#include "Wall.hpp"
#include "Core.hpp"
#include "geometry.h"

char descr[] = "muro";

Wall::Wall(line l) : Core(l.p_iniziale, char_chooser(l), descr){
    this->line_lenght=l.length;
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

int Wall::get_line_lenght() {
    return this->line_lenght;
}

bool Wall::get_alignment() {
    return this->vertical;
}


char Wall::char_chooser(line l) {
    if (l.vertical) return '|';
    else return '-';
}
