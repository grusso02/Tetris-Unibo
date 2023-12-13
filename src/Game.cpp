#include "../include/Game.hpp"
#include "../include/common_include.h" //per ncurses e altro

#define COORY 1
#define COORX 30

Game::Game(int best = 0){
    this->board1 = TetrisBoard(COORY,COORX);

    this->scores = Board(1,3,3,17);
    this->next = Board(6,6,5,9);
    this->end = false;
    //tetramino
    //next_tetramino
    this->score = 0;
    this->best_score = best;

    scores.print(0,0,"score: 0\n\nbest score: 0");
    scores.refresh();
    next.addBorder('T','T');
    next.print(0,0,"  NEXT:  ");
    next.refresh();
}