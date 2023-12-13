#pragma once
#include "./Board.hpp"
#include <ncurses.h>

class Game{
    protected:
        TetrisBoard board1;
        Board scores;
        Board next;
        bool end;
        //tetramino
        //next_tetramino
        int score;
        int best_score;
    public:
        Game(int best);
};