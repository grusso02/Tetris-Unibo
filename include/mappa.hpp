
#pragma once // per evitare ridefinizione della classe mappa -> errore compilazione
#include <ncurses.h>

class mappa{
    private:
        int altezza,larghezza;
        WINDOW *win;

    public:
        mappa(int ny,int nx,char chary,char charx);
};