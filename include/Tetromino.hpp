#pragma once

#include <cmath>

enum Moves { ROTATE, RIGHT, LEFT, DOWN };
enum Piece { O, S, Z, T, L, J, I };

class Tetromino {
  public:
    int   origin_x;
    int   origin_y;
    int   x;
    int   y;
    int   z; // Variabile contatore
    int   symmetry;
    int   orientation;
    Piece type_name;
    int*  data;

    Tetromino()
        : origin_x(0), origin_y(0), x(0), y(0), z(0), symmetry(0),
          orientation(0), data(nullptr) {}

    Tetromino(int screen_width);

    void get_piece(int screen_width);

    int* get_cells();

    void move(Moves move);
    void moveTurn(Moves move);
};