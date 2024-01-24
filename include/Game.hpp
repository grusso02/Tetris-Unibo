#pragma once

#include "Board.hpp"
#include "Tetromino.hpp"
#include <ncurses.h>

namespace tetris {
class Game {
  private:
    Board     board;
    bool      is_over;
    Tetromino tetromino;

  public:
    Game() : board(), is_over(false), tetromino() {}

    Game(int height, int width) {
        this->board = Board(height, width, 500);
        initialize();
    }

    ~Game() {}

    void initialize() {
        board.initialize();
        this->is_over = false;
        srandom(time(NULL));
        this->tetromino = Tetromino(board.getWidth());
        board.draw_piece(tetromino);
    }

    void redraw() { board.refresh(); }

    void processInput() {
        tetromino.move(DOWN);
        switch (board.getInput()) {
        case KEY_UP:
            tetromino.move(ROTATE);
            break;
        case KEY_DOWN:
            tetromino.move(DOWN);
            break;
        case KEY_RIGHT:
            tetromino.move(RIGHT);
            break;
        case KEY_LEFT:
            tetromino.move(LEFT);
            break;
        case 'p': {
            board.setTimeout(-1);
            while (board.getInput() != 'p')
                ;
            board.setTimeout(board.getTimeout());
            break;
        }
        case 'e':
            endGame();
            break;
        default:
            break;
        }
    }

    void updateState() {
        checkCollision();
        board.clear();
        board.draw_piece(tetromino);
    }

    void checkCollision() {
        mvprintw(0, 0, "%d", tetromino.origin_x);
        mvprintw(1, 0, "%d", tetromino.x);
        mvprintw(2, 0, "%d", board.getWidth());
        refresh();

        int* cells = tetromino.get_cells();
        int  x_max = 0;
        int  x_min = INT_MAX;

        for (int i = 0; i < 4; i++) {
            if (cells[2 * i] > x_max)
                x_max = cells[2 * i];
            if (cells[2 * i] < x_min)
                x_min = cells[2 * i];
            mvprintw(i, 5, "%d", cells[2 * i]);
        }

        mvprintw(0, 7, "%d", x_max);

        if ((x_max == 1 && tetromino.x == (tetromino.origin_x + 1)) ||
            (x_max == 2 && tetromino.x == tetromino.origin_x) ||
            (x_max == 3 && tetromino.x == (tetromino.origin_x - 1))) {
            tetromino.x--;
            tetromino.z -= 2;
        }

        mvprintw(1, 7, "%d", x_min);
        if ((x_min == 0 && tetromino.x == 0) ||
            (x_min == 1 && tetromino.x == -1) ||
            (x_min == 2 && tetromino.x == -2)) {
            tetromino.x++;
            tetromino.z += 2;
        }

        if (tetromino.type_name == I && x_min == 0 && tetromino.x == -1)
            tetromino.orientation =
                (tetromino.orientation + 1) % tetromino.symmetry;
    }

    bool isOver() { return is_over; }

  private:
    void endGame() { is_over = true; }
};
} // namespace tetris
