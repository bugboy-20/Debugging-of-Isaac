#include "Core.hpp"

Core::Core(coords pos, char display)
{
	this->pos = pos;
	this->display = display;
};

// Core::Core(){
// 	pos.x = 0;
// 	pos.y = 0;
// 	display = '\0';
// };
int Core::get_x() { return pos.x; };
int Core::get_y() { return pos.y; };
char Core::get_display() { return display; };