#include "../include/Mappa.hpp"
#include "../include/common_include.h" //per ncurses e altro

Mappa::Mappa(int starty, int startx, int ny, int nx, char chary, char charx) { //int starty, int startx utili?
    // inizializzo
    this->y0 = starty;
    this->x0 = startx;
    this->altezza = ny;
    this->larghezza = nx;
    WINDOW* window = newwin(ny, nx, y0, x0);
    refresh();
    this->win = window;
    // creo box
    box(win, chary, charx);
    wrefresh(win); // NOTA: refresh() NON funziona, perchè non aggiorna tutte le finestre, ma solo quella "standard"
}
Board::Board(int starty, int startx, int ny, int nx, char chary, char charx): Mappa(starty,startx,ny,nx,'!','V'){
}

void Board::draw(int y0, int x0){
    int y = y0;
    int x = x0;
    for(int i=0; i<20; i++){ // 20 righe
        wmove(win,y,x);
        wprintw(win,"<!"); // mi sposto su nuova riga e scrivo

        for(int j=0; j<10; j++){ // 10 colonne
            wprintw(win,"*");
        }

        wprintw(win,"!>");
        y++;
        x = x0;
    }
    wmove(win,y,x);
    wprintw(win,"  ");
    for(int i=0; i<10; i++){
        wprintw(win,"V");
    }
    wrefresh(win);
}