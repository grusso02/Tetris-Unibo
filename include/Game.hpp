#pragma once
#include "./Board.hpp"
#include "./Tetromino.hpp"
#include <ncurses.h>

// gestirà tutte le altre classi insieme per far funzionare il gioco (come un
// direttore che CONTROLLA tutto(=controller))
class Game {
  protected:
    TetrisBoard tetris_board;   // dove cadono i teramini
    Board       scores;         // dove si mostrano i punteggi
    Board       window_next_tetromino; // dove mostro prossimo tetramino
    bool        game_over; // ci avvisa se il gioca è finito (unica ragione per
                           // terminare)
    Tetromino tetromino;
    Tetromino next_tetromino;
    int score; // quello che è mostrato in scores
    int best_score;

  public:
    Game();                      // costruttore di default
    Game(int height, int width); // costruttore personalizzato
    bool isOver();               // ritorna true se il gioco è finito
    void endGame();              // imposta game_over a true (=finisce partita)
    bool enoughSpace(int, int, int, int);
    Moves processInput();
    void updateState();
    void draw_piece(Tetromino piece);
    void delete_piece(Tetromino piece);
    void destroyFullRows();
    void redraw();
    void checkCollision();
    bool check_piece(Tetromino piece);
};