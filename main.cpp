#include "include/Tetromino.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define NEXT_EMPTY_CELL "  "
#define PLAYFIELD_EMPTY_CELL " ."

using namespace std;

tetris::Tetromino get_piece() {
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
    cout << next_piece_random_index << endl;
    int* next_piece_data = piece_data[next_piece_random_index];

    tetris::Tetromino next_piece;

    next_piece.origin_x = 0;
    next_piece.origin_y = 0;
    next_piece.x = 0;
    next_piece.y = 0;

    next_piece.data = next_piece_data +
                      1; // Facnedo + 1 passa al primo valore delle coordinate
                         // dopo il numero di orientamenti possibili
    next_piece.symmetry = *next_piece_data;
    next_piece.orientation = random() % next_piece.symmetry;
    // strcpy(next_piece.empty_cell, NEXT_EMPTY_CELL);

    return next_piece;
}

int* get_cells(tetris::Tetromino piece) { // 2 1 1 1 2 0 1 0
    static int cells[8] = {};
    int        data = *(piece.data + piece.orientation);

    for (int i = 0; i < 4; i++) {
        cells[2 * i] =
            piece.x + ((int)(data / pow(2, (4 * i))) %
                       4); // cells[2 * i] = piece.x + ((data >> (4 * i)) & 3);
        cells[2 * i + 1] =
            piece.y +
            ((int)(data / pow(2, (4 * i + 2))) %
             4); // cells[2 * i + 1] = piece.y + ((data >> (4 * i + 2)) & 3);
    }

    return cells;
}

void draw_piece(tetris::Tetromino piece) { // 0 1 2 3 4 5 6 7
    int* cells = get_cells(piece);         // 2 1 1 1 0 2 1 0
    int  x = 0;
    int  y = 0;

    for (int i = 0; i < 4; i++) {
        x = cells[2 * i] * 2 + piece.origin_x; // 2 0 2 0
        y = cells[2 * i + 1] + piece.origin_y; // 1 1 0 0
        mvprintw(y, x, "[]");
    }
}

int main() {
    tetris::Tetromino next_piece;
    tetris::Tetromino current_piece;

    srandom(time(NULL));

    initscr();

    next_piece = get_piece();

    clear();
    draw_piece(next_piece);
    refresh();

    getch();
    endwin();
    return 0;
}
