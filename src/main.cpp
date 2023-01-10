#include <iostream>
#include "time_handle.h"
#include "Screen.hpp"
#include "Map.h"
#include "Player.hpp"
#include "physics.h"
#include "constants.h"
// #define DEBUG

#ifdef _WIN32 // sleep fn
#include <Windows.h>
#include <ncursesw/ncurses.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;

#define FRAMETIME 30       // durata di un frame ~~> velocità del gioco
#define utom(x) (1000 * x) // from micro to milli
int sleep_time(timeval start, timeval end);
void controller(Player *); // gestisce la tastiera

void exit_game(); // permette di uscire

// true se deve essere eseguito un altro menù
bool menu(Screen &); // apre il menu
void game_loop();
void controls(Screen &); // apre l'interfaccia dei controlli

map *game_map;
Player *player;
Screen schermo;

int main()
{
    int key;
    do
    {
        // init schermo e player
        schermo = Screen();
        player = new Player({ROOM_WIDTH / 2, ROOM_HEIGHT / 2});

        // apro il menu
        bool again;
        do
        {
            again = menu(schermo);
        } while (again);

        // init della mappa
        game_map = init_map(player, 1);

        game_loop();
        key = schermo.print_game_over();
        destroy_map(*game_map);
        *game_map = {NULL, NULL};
        delete player;
        schermo.stop_screen();

    } while (key != quit_button);
    exit_game();
}

bool menu(Screen &schermo)
{
    schermo.start_gamemenu();
    int selected_menu, key;

    // loop di controllo del menù
    do
    {
        schermo.gm.draw();
        key = getch();
        if (key == '\n')
        {
            selected_menu = schermo.gm.get_selected_item();
            break;
        }
        else if (key == KEY_DOWN || key == down_button)
            schermo.gm.select_next_item();
        else if (key == KEY_UP || key == up_button)
            schermo.gm.select_prev_item();
    } while (true);
    schermo.gm.clean();

    bool again = false;
    switch (selected_menu)
    {
    case NEW_GAME:
        // game loop
        break;

    case CONTROLS:
        controls(schermo);
        again = true;
        break;

    case EXIT_GAME:
        exit_game();
        break;

    default:
        exit_game(); // qualcosa è andato storto meglio uscire
        break;
    }
    return again;
}

void controls(Screen &schermo)
{
    schermo.start_gamecontrols();
    while (getch() != quit_button)
        ;
    schermo.gc.clean();
}

void game_loop()
{
    timeval inizio_frame, fine_frame;

    schermo.start_gameinterface(game_map->current_room);
    while (!game_over(*player))
    {
        // il secondo parametro è la timezone, non importa usare quella giusta basta che sia uguale ovunque
        time_now(inizio_frame);

        controller(player);

        do_room(game_map->current_room);
        schermo.gi.set_room(game_map->current_room);
        schermo.gi.handle_events();

        time_now(fine_frame);
#ifdef _WIN32
        Sleep(sleep_time(inizio_frame, fine_frame));
#else
        usleep(utom(sleep_time(inizio_frame, fine_frame))); // usleep specifica quanti micro secondi sospendere l'esecuzione
#endif
    }
}

// https://stackoverflow.com/questions/4025891/create-a-function-to-check-for-key-press-in-unix-using-ncurses
void controller(Player *player)
{
    int key;
    do
    {
        key = getch();
        if (key - '0' >= 1 && key - '0' <= player_inventory_slots)
        {
            int slot = key - '0' - 1;
            if (player->get_inventory().items[slot] != NULL)
            {
                drop_item(*game_map->current_room, slot);
            }
            continue;
        }
        switch (key)
        {
        case up_button:
            player->move_up(game_map->current_room);
            break;
        case left_button:
            player->move_left(game_map->current_room);
            break;
        case right_button:
            player->move_right(game_map->current_room);
            break;
        case down_button:
            player->move_down(game_map->current_room);
            break;

        case KEY_UP:
            bullet_creation(player, UP);
            break;
        case KEY_DOWN:
            bullet_creation(player, DOWN);
            break;
        case KEY_RIGHT:
            bullet_creation(player, RIGHT);
            break;
        case KEY_LEFT:
            bullet_creation(player, LEFT);
            break;

        case heal_button:
            player->use_potion(game_map->current_room);
            break;
#ifdef DEBUG
        case quit_button:
            exit_game();
            break;
        case 'p': // tasto suicidio
            player->set_health(0);
            break;
#endif
        default:
            break;
        }
    } while (key != ERR); // finché ci sono tasti da leggere
}

void exit_game()
{
    schermo.stop_screen();
    exit(EXIT_SUCCESS);
}

int sleep_time(timeval start, timeval end)
{
    time_t te = time_elapsed(start, end);
    if (te > FRAMETIME)
        return 0;
    return FRAMETIME - te;
}
