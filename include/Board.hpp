
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
    bool   print(int y, int x, const char* c); // ritorna false se fuori range window
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
    int timeout;

  public:
    TetrisBoard();
    TetrisBoard(int starty, int startx, int block_height, int block_width,
                int speed);
    void draw();
    bool addBlock(int y, int x); // aggiunge un blocca usando indici da 0 a
                                 // block_height-1 e da 0 a block_width-1
    bool delBlock(int y, int x);
    bool isBlock(int y, int x);
    int  lastYBlock();
    int  lastXBlock();
    bool checkRow(int y); // controlla se la riga è completa
    bool destroyRow(
        int y); // distrugge riga se completa e abbassa tutte quelle sopra
    int  getInput();
    void clear();
    int  getTimeout();
    void setTimeout(int speed);
};

class Scoreboard: public Board{ 
  public:
    Scoreboard(){};
    Scoreboard(int width, int y, int x) {
        this->win = newwin(1, width, y, x);
    }
    ~Scoreboard(){};
 
    void initialize(int intial_score) {
        clear();
        mvwprintw(win, 0, 0, "Score: ");
        updateScore(intial_score);
        refresh();
    }
 
    void updateScore(int score) {
        mvwprintw(win, 0, getWidth() - 10, "%10d", score);
    }
};

enum casesMenu {START, BEST_SCORES, EXIT};

class Menu: public Board{
  protected:

  public:
    Menu(int starty, int startx, int height, int width);
    void draw();
    int getInput();
    void items(int y);
};