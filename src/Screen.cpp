#include "Screen.hpp"

Screen::Screen()
{
    initscr();
    cbreak(); // ctrl+c behaviour
    noecho(); // avoids user input from being printed
    nodelay(stdscr, TRUE);
    curs_set(0);
    // keypad(wroom, true);
    refresh();

    wroom = newwin(ROOM_HEIGHT, ROOM_WIDTH, 1, 1);
    playerstat = newwin(4, 17, 1, ROOM_WIDTH + 2);
    box(playerstat, 0, 0);

    refresh();
    wrefresh(wroom);
    wrefresh(playerstat);
}

void Screen::render_room(room r)
{
    // pulisco lo schermo da rappresentazioni precedenti
    wclear(wroom);

    // render muri esterni
    box(wroom, 0, 0);
    print_doors(r.doors);

    // render dei muri interni (forse sono tra gli item?)

    // render degli item
    while (r.items != NULL)
    {
        mvwaddch(wroom, r.items->item.getY(), r.items->item.getX(), r.items->item.getDisplay());
        r.items = r.items->next;
    }

    // render entità
    while (r.entities != NULL)
    {
        mvwaddch(wroom, r.entities->mob->getY(), r.entities->mob->getX(), r.entities->mob->getDisplay());
        r.entities = r.entities->next;
    }

    refresh();
    wrefresh(wroom);
}

void Screen::print_doors(door *doors[])
{
    char door = ' ';

    for (int i = 0; i < 4; i++)
    {
        if (doors[i] != NULL)
        {
            int yLoc1, xLoc1, yLoc2, xLoc2;

            switch ((*doors[i]).position)
            {
            case UPPER_DOOR:
                yLoc1 = yLoc2 = 0;
                xLoc1 = (ROOM_WIDTH / 2) - 1;
                xLoc2 = (ROOM_WIDTH / 2);
                break;
            case LOWER_DOOR:
                yLoc1 = yLoc2 = ROOM_HEIGHT - 1;
                xLoc1 = (ROOM_WIDTH / 2) - 1;
                xLoc2 = (ROOM_WIDTH / 2);
                break;
            case RIGHT_DOOR:
                yLoc1 = (ROOM_HEIGHT / 2) - 1;
                yLoc2 = (ROOM_HEIGHT / 2);
                xLoc1 = xLoc2 = ROOM_WIDTH - 1;
                break;
            case LEFT_DOOR:
                yLoc1 = (ROOM_HEIGHT / 2) - 1;
                yLoc2 = (ROOM_HEIGHT / 2);
                xLoc1 = xLoc2 = 0;
                break;

            default:
                // printw("%s", "sus");
                break;
            }
            mvwaddch(wroom, yLoc1, xLoc1, door);
            mvwaddch(wroom, yLoc2, xLoc2, door);
        }
    }
}

void Screen::render_playerstat(room r)
{
    // printw("entities: %s", typeid(Entity).name());
    wmove(playerstat, 1, 1);
    wprintw(playerstat, "%s: ", r.entities->mob->name); // ho usato il campo name come se fosse pubblico
    int nchars = r.entities->mob->health / 2;           // servono funzioni getter
    for (int i = 0; i < 5; i++)
    {
        if (nchars > 0)
        {
            waddch(playerstat, 'O');
            nchars--;
        }
        else
            waddch(playerstat, 'o');
    }
    refresh();
    wrefresh(playerstat);
}

void Screen::stop_screen()
{
    endwin();
}