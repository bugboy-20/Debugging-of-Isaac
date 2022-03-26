#include <bits/types/time_t.h>
#include <cstddef>
#include <iostream>
#include <ctime>
#include "Map.h"
#include "Player.hpp"

#ifdef _WIN32 // sleep fn
#include <Windows.h>
#include <ncursesw/ncurses.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;


#define FRAMETIME 250 //durata di un frame ~~ velocità del gioco
void controller(Player); // è solamente dimostrativa ma sicuramente ci sarà qualcosa del genere

//dummy class and funtions
//  [andranno poi implementate]
class Screen {
    public:
        void print(room r);
};

void do_room(room *r); //fa cose sulla stanza

bool game_over();

map *dummy_map;

room a{ //stanza finta
    NULL, //nessun oggetto
    NULL, //nessun mob
    { //2 porte (una sopra e una a destra
        new door {
            RIGHT_ROOM,
            NULL
        },
        new door {
            UPPER_ROOM,
            NULL
        },
        NULL,
        NULL
    }
};


int main() {
    //init schermo
    time_t inizio_frame, fine_frame;
    Screen schermo = Screen();
    //init della mappa
    dummy_map=init_map(a);
    //init del player
    Player player = Player();

    //game loop
    while (!game_over()) {
        inizio_frame=time(0);

        controller(player);
        do_room(dummy_map->current_room);
        schermo.print(*dummy_map->current_room);

        fine_frame=time(0);
        usleep(1000*(FRAMETIME-(fine_frame-inizio_frame))); //usleep specifica quanti micro secondi sospendere l'esecuzione
    }

}

// https://stackoverflow.com/questions/4025891/create-a-function-to-check-for-key-press-in-unix-using-ncurses
void controller(Player player) {
    int key;
    do {
        key = getch();
        switch (key) {
            case 'w':
                player.move_up(*dummy_map->current_room);
                /*
                 * PREMETTO CHE È SOLO UN ESEMPIO. L'ho pensato come un metodo della classe Player che richiama un metodo privato del tipo
                 * move( const room r, int x, int y) {
                 *      if(!collision(this->x,this->y,r)) // collision è un metodo fatto da Saad che ritorna True quando nella posizione c'è già un oggetto incompenetrabile della stanza
                 *          this->x += x
                 *          this->y += y
                 * }
                 */
                break;
            default: break;
            // ...
        }
    } while (key != ERR);  //finché ci sono tasti da leggere
}
