#pragma once

struct coords
{
    int x, y;
};

struct rectangle
{
    // vertici della diagonale
    coords p1, p2;
};

struct line {
    coords p_iniziale;
    bool vertical;
    int length;
};
