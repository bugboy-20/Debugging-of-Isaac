#include <ncursesw/ncurses.h>

class Screen
{
private:
    WINDOW room;

public:
    Screen();
    // stampa sullo schermo l'intera stanza
    renderRoom(room r);

    // stampa sullo schermp solo gli elementi che possono spostarsi (muri ecc)
    updateRoom(room r); // per ora propongo entrambi i metodi
                        // ma si può anche scegliere di usare un solo metodo se preferite
};
