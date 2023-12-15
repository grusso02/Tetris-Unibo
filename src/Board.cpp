#include "../include/Board.hpp"
#include "../include/common_include.h" //per ncurses e altro

Board::Board(){}
Board::Board(int n_rows, int n_columns, int start_y, int start_x) { //int starty, int startx utili?
    // inizializzo
    this->height = n_rows;
    this->width = n_columns;
    this->win = newwin(height, width, start_y, start_x);

    //se vuoi box, usa this->addborder()
}
void Board::refresh(){
    wrefresh(this->win); // NOTA: refresh() NON funziona, perchè non aggiorna tutte le finestre, ma solo "stdscr"(STanDardSCReen)
}
void Board::clear(){
    wclear(this->win);
}
bool Board::addchar(int y, int x, char c){
    if(y < this->height && x < this->width){
        wmove(this->win,y,x);
        waddch(win,c);
        return true;
    }
    else return false;
}
bool Board::print(int y, int x,const char *c){
    if(y < this->height && x < this->width){
        wmove(this->win,y,x);
        wprintw(win,c);
        return true;
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

TetrisBoard::TetrisBoard(){}
TetrisBoard::TetrisBoard(int starty, int startx, int row_blocks, int column_blocks): Board(row_blocks+1,(column_blocks*2)+4,starty,startx){
    // dell'inizializzazione degli altri parametri se ne occupa il costruttore della supercalsse
    this->block_height = row_blocks;
    this->block_width = column_blocks;
    this->clear();
    this->draw(); // prende n_righe e n_colonne
}
void TetrisBoard::draw(){
    int y = 0; //nota y e x sono relativi alla vindow attuale
    int x = 0;
    for(int i=0; i<block_height; i++){ // per ogni riga(std = 20)
        wmove(win,y,x); // mi sposto su nuova riga
        wprintw(win,"<!"); // e scrivo

        for(int j=0; j<block_width; j++){ // per ogni colonna (std = 10) (ogni colonna sono 2 caratteri)
            wprintw(win,". "); //carattere "·" non va
        }

        wprintw(win,"!>");
        // mi preparo a spostare cursore
        y++;
        x = 0;
    }
    wmove(win,y,x);
    wprintw(win,"  ");
    for(int i=0; i<block_width ; i++){
        wprintw(win,"\\/"); // disegno il fondo
    }
    wrefresh(win);
}
bool TetrisBoard::cancelCell(int y, int x){
    if(y < this->height && x < this->width && x%2 == 0){
        wmove(this->win,y,x);
        wprintw(win,". ");
        return true;
    }
    else 
        return false;
}