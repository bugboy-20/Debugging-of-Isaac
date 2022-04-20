#pragma once

#include "Core.hpp"
#include "geometry.h"
class Wall : public Core {
    public:
        Wall(line, char display);
 // restituisce true qual'ora la posizione appartierne al muro
        bool is_wall(coords);
    private:
        int line_lenght;
        bool vertical;
};
