#pragma once

#include "Tetromino.hpp"
#include "Time.hpp"
#include <ncurses.h>

namespace tetris {
class Board {
  private:
    WINDOW* board;
    int     height, width, start_row, start_col;
    int     timeout;

  public:
    Board() : height(0), width(0) {}

    Board(int h, int w, int speed) : height(h), width(w) {
        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        this->start_row = ((yMax / 2) - (this->height / 2));
        this->start_col = ((xMax / 2) - (this->width / 2));
        this->timeout = speed;
        this->board = newwin(height, width, start_row, start_col);
        keypad(board, true);
        setTimeout(speed);
    };

    int getHeight() { return height; }

    int getWidth() { return width; }

    void initialize() {
        clear();
        refresh();
    }

    void addBorder() { box(board, 0, 0); }

    void refresh() { wrefresh(board); }

    void clear() {
        wclear(board);
        addBorder();
    }

    void draw_piece(tetris::Tetromino piece) {
        int* cells = piece.get_cells();
        int  print_x = 0;
        int  print_y = 0;

        for (int i = 0; i < 4; i++) {
            print_x = cells[2 * i] * 2 + piece.origin_x;
            print_y = cells[2 * i + 1] + piece.origin_y;
            mvwprintw(board, print_y, print_x + piece.z, "[]");
        }
    }

    int getInput() {
        chtype input = wgetch(board);

        return input;
    }

    chtype getCharAt(int y, int x) { return (mvwinch(board, y, x)); }

    int  getTimeout() { return timeout; }
    void setTimeout(int speed) { wtimeout(board, speed); }

    int getStartRow() { return start_row; }

    int getStartCol() { return start_col; }
};
} // namespace tetris
