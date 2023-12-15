#include "../include/Game.hpp"
#include "../include/common_include.h" //per ncurses e altro

#define COORY 1
#define COORX 30
#define BLOCKY 20
#define BLOCKX 10

//Game::Game(): tetris_board(), scores(), next_tetromino(), game_over(false), score(0),best_score(0){
    /* // equivalentemente:
    game_over = false;
    score = 0;
    best_score = 0;
    */
//}

Game::Game(int a){ //(chiamato quando )serve a inizializzare tutti i parametri(=variabili) della classe
    //NOTA: se non prende almeno un input, il compilatore per qualche 
    //ragione lo tratta come un costruttore standard e ne ignora il contenuto?
    
    this->tetris_board = TetrisBoard(COORY,COORX,BLOCKY,BLOCKX);
    this->scores = Board(3,17,1,3);
    this->next_tetromino = Board(5,9,6,6);
    this->game_over = false;
    //tetromino
    //next_tetromino
    this->score = 0;
    //this->best_score = apriFile(...);

    //inizializzo finestra "scores"
    scores.print(0,0,"score: 0\n\nbest score: 0");
    scores.refresh();
    //inizializzo finestra "next_tetromino"
    next_tetromino.addBorder('T','T');
    next_tetromino.print(0,0,"  NEXT:  ");
    next_tetromino.refresh();
}

bool Game::isOver(){
    return this->game_over;
}

void Game::endGame(){
    this->game_over = true;
}