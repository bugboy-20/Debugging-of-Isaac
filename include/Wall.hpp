#pragma once

#include "Core.hpp"
#include "geometry.h"
class Wall : public Core {
    public:
        Wall(line);
 // restituisce true qual'ora la posizione appartierne al muro
        bool is_wall(coords);
        int get_line_lenght();

    // true se è verticale, false se è orizzontale
        bool get_alignment();
    private:
        int line_lenght;  //length
        bool vertical;

        // serve grafica più carina al muro
        char char_chooser(line);
};
