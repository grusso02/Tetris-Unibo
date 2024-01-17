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
    static int o_piece[] = {1, 0x1256};
    static int s_piece[] = {2, 0x4512, 0x0459};
    static int z_piece[] = {2, 0x0156, 0x1548};
    static int t_piece[] = {4, 0x1456, 0x1596, 0x4569, 0x4159};
    static int l_piece[] = {4, 0x159a, 0x8456, 0x0159, 0x2654};
    static int j_piece[] = {4, 0x1598, 0x0456, 0x2159, 0xa654};
    static int i_piece[] = {2, 0x159d, 0x4567};

    static int* piece_data[] = {
        o_piece, s_piece, z_piece, t_piece, l_piece, j_piece, i_piece,
    };
    static int piece_data_len = 7;
    int        next_piece_random_index = rand() % piece_data_len;
    cout << next_piece_random_index << endl;
    int* next_piece_data = piece_data[next_piece_random_index];

    tetris::Tetromino next_piece;

    next_piece.origin_x = 5;
    next_piece.origin_y = 5;
    next_piece.x = 0;
    next_piece.y = 0;

    next_piece.data = next_piece_data +
                      1; // Facnedo + 1 passa al primo valore delle coordinate
                         // dopo il numero di orientamenti possibili
    next_piece.symmetry = *next_piece_data;
    next_piece.orientation = rand() % next_piece.symmetry;
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

    srand((unsigned)time(0));

    initscr();

    next_piece = get_piece();

    clear();
    draw_piece(next_piece);
    refresh();

    getch();
    endwin();
    return 0;
}
