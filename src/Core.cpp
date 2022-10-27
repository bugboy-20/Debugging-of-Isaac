#include "Core.hpp"
#include <cstring>


Core::Core(coords pos, char display, char description[], bool crossable)
{
    this->pos = pos;
    this->display = display;
    this->crossable = crossable;
    strcpy(this->description, description);
}

int Core::get_x() { return pos.x; }
int Core::get_y() { return pos.y; }
char Core::get_display() { return display; }
char *Core::get_description()
{
    char *desc = new char[20];
    strcpy(desc, this->description);
    return desc;
}
void Core::get_description(char d[20]) { strcpy(d, this->description); }
