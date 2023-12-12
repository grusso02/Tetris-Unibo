#include "../include/Board.hpp"
#include "../include/common_include.h" //per ncurses e altro

Board::Board(int starty, int startx, int ny, int nx, char chary, char charx) { //int starty, int startx utili?
    // inizializzo
    this->y0 = starty;
    this->x0 = startx;
    this->height = ny;
    this->width = nx;
    this->win = newwin(ny, nx, y0, x0);

    // creo box
    this->addBorder(chary,charx);
}
void Board::refresh(){
    wrefresh(this->win); // NOTA: refresh() NON funziona, perchè non aggiorna tutte le finestre, ma solo "stdscr"(STanDardSCReen)
}
void Board::clear(){
    wclear(this->win);
}
bool Board::print(int y, int x, char c){
    if(y < this->height && x < this->width){
        wmove(this->win,y,x);
        waddch(win,c);
    }
    else return false;
}
char Board::getChar(int y, int x){
    return mvwinch(this->win,y,x);
}
void Board::addBorder(char chary, char charx){
    box(this->win, chary, charx);
}
int Board::getHeight(){
    return this->height;
}
int Board::getWidth(){
    return this->width;
}
//char Board::getInput(){}

//***********SOTTOCLASSE

TetrisBoard::TetrisBoard(int starty, int startx): Board(starty,startx,21,24,' ',' '){
    Board::clear();
    draw(starty,startx);
}
void TetrisBoard::draw(int y0, int x0){
    int y = y0;
    int x = x0;
    for(int i=0; i<20; i++){ // 20 righe
        wmove(win,y,x); // mi sposto su nuova riga
        wprintw(win,"<!"); // e scrivo

        for(int j=0; j<10; j++){ // 10 colonne (ogni colonna sono 2 caratteri)
            wprintw(win,"..");
        }

        wprintw(win,"!>");
        // mi preparo a spostare cursore
        y++;
        x = x0;
    }
    wmove(win,y,x);
    wprintw(win,"  ");
    for(int i=0; i<10; i++){
        wprintw(win,"VV"); // disegno il fondo
    }
    wrefresh(win);
}