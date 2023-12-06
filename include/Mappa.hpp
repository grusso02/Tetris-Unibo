
#pragma once // per evitare ridefinizione della classe mappa -> errore compilazione
#include <ncurses.h>

class Mappa {
    protected:
        int y0, x0;
        int altezza, larghezza;
        WINDOW* win;

    public:
        Mappa(int starty, int startx, int ny, int nx, char chary, char charx);
};

class Board: public Mappa {
    public:
        Board(int starty, int startx, int ny, int nx, char chary, char charx);
        void draw(int y0, int x0);
};