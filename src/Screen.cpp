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

    int start_y, start_x; // variabili inutili, solo per sapere ogni valore cosa significa
    room_height = 20;
    room_width = 100;
    // start_y = (room_height / 2) - 1;
    // start_x = (room_width / 2) - 1;

    wroom = newwin(room_height, room_width, 1, 1);
    refresh();
}

void Screen::render_room(room r)
{
    // pulisco lo schermo da rappresentazioni precedenti
    wclear(wroom);
    // refresh();
    // wrefresh(wroom);

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
        // printw("(%d,%d)", r.entities->mob.getX(), r.entities->mob.getY());

        mvwaddch(wroom, r.entities->mob->getY(), r.entities->mob->getX(), r.entities->mob->getDisplay());
        r.entities = r.entities->next;
    }

    refresh();
    wrefresh(wroom);
}

void Screen::print_doors(door *doors[])
{
    char door = 254;

    for (int i = 0; i < 4; i++)
    {
        if ((doors + i) != NULL)
        {
            int yLoc1, xLoc1, yLoc2, xLoc2;
            switch ((*doors)[i].position)
            {
            case UPPER_DOOR:
                yLoc1 = yLoc2 = 0;
                xLoc1 = (room_width / 2) - 1;
                xLoc2 = (room_width / 2);
                break;
            case LOWER_DOOR:
                yLoc1 = yLoc2 = room_height - 1;
                xLoc1 = (room_width / 2) - 1;
                xLoc2 = (room_width / 2);
                break;
            case RIGHT_DOOR:
                yLoc1 = (room_height / 2) - 1;
                yLoc2 = (room_height / 2);
                xLoc1 = xLoc2 = room_width - 1;
                break;
            case LEFT_DOOR:
                yLoc1 = (room_height / 2) - 1;
                yLoc2 = (room_height / 2);
                xLoc1 = xLoc2 = 0;
                break;

            default:
                break;
            }
            mvwaddch(wroom, yLoc1, xLoc1, door);
            mvwaddch(wroom, yLoc2, xLoc2, door);
        }
    }
    wrefresh(wroom);
}

void Screen::stop_screen()
{
    endwin();
}