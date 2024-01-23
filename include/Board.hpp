
#pragma once // per evitare ridefinizione della classe Board -> errore compilazione
#include <ncurses.h>

// Board è una classe che serve solo a gestire le WINDOW di ncurses
class Board {
    protected:
        // int y0, x0; non dovrebbero servire MAI
        int height, width;
        WINDOW* win;

    public:
        Board();
        Board(int num_rows, int num_columns, int start_y, int start_x);
        void refresh(); // volendo si può inserire dentro print
        void clear();
        bool addchar(int y, int x, char c);
        bool print(int y, int x,const char *c); //ritorna false se fuori range window
        char getChar(int y, int x);
        void addBorder(char chary, char charx);
        int getHeight();
        int getWidth();
        //char getInput();
};

//TetrisBoard è una specializzazione di Board che si occupa solo di WINDOW create per un campo da tetramini
class TetrisBoard: public Board { //di dimensioni prefissate per "campo da tetris"
    protected:
        int block_height;
        int block_width;
    public:
        TetrisBoard();
        TetrisBoard(int starty, int startx, int block_height, int vlock_width);
        void draw();
        bool cancelCell(int y, int x);
};