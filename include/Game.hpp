#pragma once
#include "../include/Game.hpp"
#include "./Board.hpp"
#include "./Tetromino.hpp"
#include <ctime>
#include <iostream>
#include <limits.h>
#include <ncurses.h>

#define START_Y 1
// #define COORX 30
#define BLOCKY 20
#define BLOCKX 10

// gestirà tutte le altre classi insieme per far funzionare il gioco (come un
// direttore che CONTROLLA tutto(=controller))
class Game {
  protected:
    TetrisBoard tetris_board;          // dove cadono i teramini
    Scoreboard  score_board;           // dove si mostrano i punteggi
    Board       window_next_tetromino; // dove mostro prossimo tetramino

    Tetromino tetromino;
    Tetromino next_tetromino;

    int  score; // quello che è mostrato in scores
    int  best_score;
    bool game_over; // ci avvisa se il gioca è finito (unica ragione per
                    // terminare)

  public:
    Game();                      // costruttore di default
    Game(int height, int width); // costruttore personalizzato
    ~Game();

    bool  isOver();  // ritorna true se il gioco è finito
    void  endGame(); // imposta game_over a true (=finisce partita)
    bool  enoughSpace(int, int, int, int);
    Moves processInput();
    void  updateState();
    void  draw_piece(Tetromino piece);
    void  draw_next_piece(Tetromino piece);
    void  delete_piece(Tetromino piece);
    void  checkCollision(Moves m);
    bool  check_floor_and_piece();
    void  destroyFullRows();
    void  redraw();
    int   getScore();
};