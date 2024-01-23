#pragma once
#include "./Board.hpp"
#include <ncurses.h>

//gestirà tutte le altre classi insieme per far funzionare il gioco (come un direttore che CONTROLLA tutto(=controller))
class Game{
    protected:
        TetrisBoard tetris_board; //dove cadono i teramini
        Board scores; // dove si mostrano i punteggi
        Board next_tetromino; // dove mostro prossimo tetramino
        bool game_over; // ci avvisa se il gioca è finito (unica ragione per terminare)
        //tetramino
        //next_tetramino
        int score; // quello che è mostrato in scores
        int best_score;
    public:
        //Game(); // costruttore di default
        Game(int a); // costruttore personalizzato
        bool isOver(); // ritorna true se il gioco è finito
        void endGame(); // imposta game_over a true (=finisce partita)
        bool enoughSpace(int,int,int,int);
        void processInput(); // TO DO
        void updateState(); // TO DO
        void redraw(); // TO DO
};