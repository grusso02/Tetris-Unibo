#include "include/Tetromino.h"
#include <iostream>
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define NEXT_EMPTY_CELL "  "
#define PLAYFIELD_EMPTY_CELL " ."

using namespace std;

int* get_cells(tetris::Tetromino piece) {
    static int cells[8] = {};
    int        data = *(piece.data + piece.orientation);
    int        x = piece.x;
    int        y = piece.y;

    for (int i = 0; i < 4; i++) {
        cells[2 * i] = x + ((data >> (4 * i)) & 3);
        cells[2 * i + 1] = y + ((data >> (4 * i + 2)) & 3);
    }

    return cells;
}

void draw_piece(tetris::Tetromino piece) {
    int  i = 0;
    int* cells = get_cells(piece);
    int  x = 0;
    int  y = 0;

    for (i = 0; i < 4; i++) {
        x = cells[2 * i] * 2 + piece.origin_x;
        y = cells[2 * i + 1] + piece.origin_y;
        mvprintw(y, x, "[]");
    }
}

tetris::Tetromino get_piece() {
    static int square_data[] = {1, 0x1256};
    static int line_data[] = {2, 0x159d, 0x4567};
    static int s_data[] = {2, 0x4512, 0x0459};
    static int z_data[] = {2, 0x0156, 0x1548};
    static int l_data[] = {4, 0x159a, 0x8456, 0x0159, 0x2654};
    static int r_data[] = {4, 0x1598, 0x0456, 0x2159, 0xa654};
    static int t_data[] = {4, 0x1456, 0x1596, 0x4569, 0x4159};

    static int* piece_data[] = {square_data, line_data, s_data, z_data,
                                l_data,      r_data,    t_data};
    static int piece_data_len = sizeof(piece_data) / sizeof(piece_data[0]);
    int               next_piece_index = random() % piece_data_len;
    int*              next_piece_data = piece_data[next_piece_index];

    tetris::Tetromino next_piece;

    next_piece.origin_x = 0;
    next_piece.origin_y = 0;
    next_piece.x = 0;
    next_piece.y = 0;

    next_piece.data = next_piece_data + 1;
    next_piece.symmetry = *next_piece_data;
    next_piece.orientation = random() % next_piece.symmetry;
    strcpy(next_piece.empty_cell, NEXT_EMPTY_CELL);

    return next_piece;
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
