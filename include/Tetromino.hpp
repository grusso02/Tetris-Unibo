#pragma once

#include <cmath>

namespace tetris {

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

    Tetromino(int screen_width) { get_piece(screen_width); }

    void get_piece(int screen_width) {
        static int o_piece[] = {1, 0x5410};
        static int s_piece[] = {2, 0x4521, 0x9540};
        static int z_piece[] = {2, 0x6510, 0x8451};
        static int t_piece[] = {4, 0x4561, 0x5961, 0x9654, 0x4951};
        static int l_piece[] = {4, 0x4562, 0x59A1, 0x8654, 0x9510};
        static int j_piece[] = {4, 0x4560, 0x5921, 0xA654, 0x8951};
        static int i_piece[] = {2, 0x7654, 0xEA62};

        static int* piece_data[] = {
            o_piece, s_piece, z_piece, t_piece, l_piece, j_piece, i_piece,
        };
        static int piece_data_len = 7;
        int        next_piece_random_index = random() % piece_data_len;
        type_name = static_cast<Piece>(next_piece_random_index);
        int* next_piece_data = piece_data[next_piece_random_index];

        origin_x = (screen_width - 4) / 2;
        origin_y = 1;
        x = origin_x / 2 + 1;
        y = 0;
        z = 0;

        data = next_piece_data + 1;
        symmetry = *next_piece_data;
        orientation = random() % symmetry;
    }

    int* get_cells() {
        static int cells[8] = {};
        int        _data = *(data + orientation);

        for (int i = 0; i < 4; i++) {
            cells[2 * i] = ((int)(_data / pow(2, (4 * i))) % 4);
            cells[2 * i + 1] = y + ((int)(_data / pow(2, (4 * i + 2))) % 4);
        }

        return cells;
    }

    void move(Moves move) {
        switch (move) {
        case ROTATE:
            orientation = (orientation + 1) % symmetry;
            break;
        case RIGHT: {
            x = x + 1;
            z += 2;
            break;
        }
        case LEFT: {
            x = x - 1;
            z -= 2;
            break;
        }
        case DOWN:
            y = y + 1;
            break;
        default:
            break;
        }
    }
};

} // namespace tetris