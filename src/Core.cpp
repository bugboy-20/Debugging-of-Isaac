#include "Core.hpp"
#include <cstring>

Core::Core(coords pos, char display, const char description[STR_LENGTH], bool crossable)
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
    char *desc = new char[STR_LENGTH];
    strcpy(desc, this->description);
    return desc;
}
void Core::get_description(char d[STR_LENGTH]) { strcpy(d, this->description); }
bool Core::is_crossable() { return crossable; }
