
#pragma once // per evitare ridefinizione della classe Board -> errore
             // compilazione
#include "./Tetromino.hpp"
#include <ncurses.h>

// Board è una classe che serve solo a gestire le WINDOW di ncurses
class Board {
  protected:
    // int y0, x0; non dovrebbero servire MAI
    int     height, width;
    int     border_width;
    WINDOW* win;

  public:
    Board();
    Board(int start_y, int start_x, int height, int width);
    void   refresh(); // volendo si può inserire dentro print
    void   clear();
    bool   addChar(int y, int x, char c);
    bool   delChar(int y, int x);
    bool   print(int y, int x,
                 const char* c); // ritorna false se fuori range window
    chtype getChar(int y, int x);
    void   addBorder(char chary, char charx);
    int    getHeight();
    int    getWidth();
    // char getInput();
};

// TetrisBoard è una specializzazione di Board che si occupa solo di WINDOW
// create per un campo da tetramini
class TetrisBoard
    : public Board { // di dimensioni prefissate per "campo da tetris"
  protected:
    int block_height; // numero di blocchi per colonna
    int block_width;  // numero di blocchi per riga

  public:
    TetrisBoard();
    TetrisBoard(int starty, int startx, int block_height, int block_width);
    void draw();
    bool addBlock(int y, int x); // aggiunge un blocca usando indici da 0 a
                                 // block_height-1 e da 0 a block_width-1
    bool delBlock(int y, int x);
    bool isBlock(int y, int x);
    bool checkRow(int y); // controlla se la riga è completa
    bool destroyRow(
        int y); // distrugge riga se completa e abbassa tutte quelle sopra
    void draw_piece(Tetromino piece);
    int  getInput();
};