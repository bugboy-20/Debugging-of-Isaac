#pragma once
struct coords{int x,y;};

class Core{
protected:
    coords pos;
    char display;
public:
    Core(int pos.x,int pos.y, char display);
    int getX();
    int getY();
    char getDisplay();
};
 