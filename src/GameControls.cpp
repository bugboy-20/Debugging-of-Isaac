#include "GameControls.hpp"
#include "constants.h"

GameControls::GameControls(WINDOW *w)
{
    this->controls = w;
    box(controls, 0, 0);

    int start_y = 5, start_x = 10, padding = 10;
    int curr_y = start_y, curr_x = start_x;

    // tasti di movimento
    mvwaddch(controls, curr_y, curr_x, up_button);
    curr_x += padding;
    mvwprintw(controls, curr_y, curr_x, "%s", "movimento");
    curr_x -= padding;
    curr_x -= 2;
    curr_y += 1;
    mvwprintw(controls, curr_y, curr_x, "%c %c %c", left_button, down_button, right_button);

    // tasti per attaccare
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(controls, curr_y, curr_x, '^');
    curr_x += padding;
    mvwprintw(controls, curr_y, curr_x, "%s", "attacco");
    curr_x -= padding;
    curr_x -= 2;
    curr_y += 1;
    mvwprintw(controls, curr_y, curr_x, "%c %c %c", '<', 'v', '>');

    // drop item dell'inventario
    curr_x = start_x - 4;
    curr_y += 4;
    for (int i = 1; i < player_inventory_slots + 1; i++)
    {
        mvwaddch(controls, curr_y, curr_x, i + '0');
        curr_x += 2;
    }
    curr_x = start_x + padding;
    mvwprintw(controls, curr_y, curr_x, "%s", "lascia gli oggetti dell'inventario");
    curr_x -= padding;

    // cura
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(controls, curr_y, curr_x, heal_button);
    curr_x += padding;
    mvwprintw(controls, curr_y, curr_x, "%s", "cura");
    curr_x -= padding;

    // uscita dal gioco
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(controls, curr_y, curr_x, quit_button);
    curr_x += padding;
    mvwprintw(controls, curr_y, curr_x, "%s", "esci dal gioco");
    curr_x -= padding;

    // testo finale
    int max_y, max_x;
    getmaxyx(controls, max_y, max_x);
    mvwprintw(controls, max_y - 2, 1, "%s", "premi q per tornare al menu` principale");

    wrefresh(this->controls);
}
void GameControls::clean()
{
    wclear(controls);
    wrefresh(controls);
    clear();
    refresh();
    delwin(controls);
}