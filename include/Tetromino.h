#pragma once

namespace tetris {
struct Tetromino {
    int  origin_x;
    int  origin_y;
    int  x;
    int  y;
    int  symmetry;
    int  orientation;
    int* data;
    char empty_cell[3];

    Tetromino() {}
    ~Tetromino() {}
};

} // namespace tetris