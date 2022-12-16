#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

class GameControls
{
private:
    WINDOW *controls;

public:
    GameControls() = default;
    GameControls(WINDOW *);
    void clean();
};