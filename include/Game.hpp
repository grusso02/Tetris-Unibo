#pragma once
#include "./Board.hpp"
#include <ncurses.h>

class Game{
    protected:
        TetrisBoard tetris_board; //dove cadono i teramini
        Board scores; // dove si mostrano i punteggi
        Board next_tetromino;
        bool game_over; // ci avvisa se il gioca è finito (unica ragione per terminare)
        //tetramino
        //next_tetramino
        int score; // quello che è mostrato in scores
        int best_score;
    public:
        Game(); // costruttore di default è ammesso
        Game(int best); // costruttore più utile personalizzato
        bool isOver(); // ritorna true se il gioco è finito
        void endGame(); // sets game_over a true (finisce partita)
        void processInput();
        void updateState();
        void redraw();
};