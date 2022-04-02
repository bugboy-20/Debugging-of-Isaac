#pragma once
struct coords{int x,y;};

class Core{
protected:
    coords pos;
    char display;
//public:
    int getX();
    int getY();
    char getDisplay();
};
 