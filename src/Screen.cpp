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

    int lateral_width = 20,
        lower_height = 10,
        playerstat_height = 4,
        legend_height = (ROOM_HEIGHT + lower_height - playerstat_height) / 2,
        inventory_height = ROOM_HEIGHT + lower_height - playerstat_height - legend_height,
        moblist_width = ROOM_WIDTH,
        start_x = 1,
        start_y = 0,
        lateral_start_x = ROOM_WIDTH + 1 + start_x,
        lower_start_y = ROOM_HEIGHT;

    wroom = newwin(ROOM_HEIGHT, ROOM_WIDTH, start_y, start_x);
    playerstat = newwin(playerstat_height, lateral_width, start_y, lateral_start_x);
    legend = newwin(legend_height, lateral_width, playerstat_height + start_y, lateral_start_x);
    inventory = newwin(inventory_height, lateral_width, playerstat_height + legend_height + start_y, lateral_start_x);
    moblist = newwin(lower_height, moblist_width, lower_start_y + start_y, start_x);
    box(playerstat, 0, 0);
    box(legend, 0, 0);
    box(inventory, 0, 0);
    box(moblist, 0, 0);

    refresh();
    wrefresh(wroom);
    wrefresh(playerstat);
    wrefresh(legend);
    wrefresh(inventory);
    wrefresh(moblist);
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
    wmove(playerstat, 2, 1);
    wprintw(playerstat, "%s: ", "punti");

    refresh();
    wrefresh(playerstat);
}

void Screen::stop_screen()
{
    endwin();
}