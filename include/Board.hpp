
#pragma once // per evitare ridefinizione della classe Board -> errore compilazione
#include <ncurses.h>

class Board {
    protected:
        int y0, x0;
        int height, width;
        WINDOW* win;

    public:
        Board(int starty, int startx, int ny, int nx, char chary, char charx);
        void refresh(); // volendo si può inserire dentro print
        void clear();
        bool print(int y, int x, char c); //ritorna false se fuori range window
        char getChar(int y, int x);
        void addBorder(char chary, char charx);
        int getHeight();
        int getWidth();
        //char getInput();
};

class TetrisBoard: public Board { //di dimensioni prefissate per "campo da tetris"
    public:
        TetrisBoard(int starty, int startx);
        void draw(int y0, int x0);
};