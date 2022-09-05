#include "Core.hpp"
#include <cstring>

Core::Core(coords pos, char display, char description[])
{
	this->pos = pos;
	this->display = display;
	strcpy(this->description, description);
};

// Core::Core(){
// 	pos.x = 0;
// 	pos.y = 0;
// 	display = '\0';
// };
int Core::get_x() { return pos.x; };
int Core::get_y() { return pos.y; };
char Core::get_display() { return display; };
char *Core::get_description()
{
	char *desc = new char[20];
	strcpy(desc, this->description);
	return desc;
}
void Core::get_description(char d[20]) { strcpy(d, this->description); }