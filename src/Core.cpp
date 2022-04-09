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
int Core::getX() { return pos.x; };
int Core::getY() { return pos.y; };
char Core::getDisplay() { return display; };