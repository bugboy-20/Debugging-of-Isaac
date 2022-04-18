#pragma once

#include "Core.hpp"
#include "geometry.h"
class Wall : public Core {
    public:
        Wall(line, char display);
        bool is_wall(coords); // restituisce true qual'ora la posizione appartierne al muro
    private:
        int line_lenght;
        bool vertical;
};
