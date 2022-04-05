#pragma once
struct coords{int x,y;};

class Core{
protected:
    coords pos;
    char display;
public:
    Core(coords pos, char display);
    int getX();
    int getY();
    char getDisplay();
};
 