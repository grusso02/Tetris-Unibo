#include "../include/Board.hpp"

Board::Board() {}

Board::Board(int start_y, int start_x, int height, int width) {
    // inizializzo
    this->height = height;
    this->width = width;
    this->win = newwin(height, width, start_y, start_x);
    this->border_width = 0;
    // se vuoi border, usa this->addborder() (cambia anche border_width)
}

void Board::refresh() {
    wrefresh(this->win); // NOTA: refresh() NON funziona, perchè non aggiorna
                         // tutte le finestre, ma solo "stdscr"(STanDardSCReen)
}

void Board::clear() { wclear(this->win); }

bool Board::addChar(int y, int x, char c) {
    if (y < this->height && x < this->width) {
        wmove(this->win, y, x);
        waddch(win, c);
        return true;
    } else
        return false;
}

bool Board::delChar(int y, int x) {
    if (y < this->height && x < this->width) {
        wmove(this->win, y, x);
        waddch(win, ' ');
        return true;
    } else
        return false;
}

bool Board::print(int y, int x, const char* c) {
    if (y < this->height && x < this->width) {
        wmove(this->win, y, x);
        wprintw(win, c);
        return true;
    } else
        return false;
}

chtype Board::getChar(int y, int x) { return mvwinch(this->win, y, x); }

void Board::addBorder(char chary, char charx) {
    box(this->win, chary, charx);
    this->border_width = 1;
}

int Board::getHeight() { return this->height; }

int Board::getWidth() { return this->width; }

// char Board::getInput(){}

//***********SOTTOCLASSE

TetrisBoard::TetrisBoard() {}

TetrisBoard::TetrisBoard(int starty, int startx, int height, int width,
                         int speed)
    : Board(starty, startx, height + 1, width + 4) { // spazio per bordo
    this->border_width = 2;
    this->block_height = height - 1; // 1 = fondo
    this->block_width = width / 2;
    this->clear();
    this->draw(); // prende n_righe e n_colonne
    // draw() inizializza border_width
    keypad(this->win, true);
    setTimeout(speed);
}

void TetrisBoard::clear() {
    wclear(this->win);
    draw();
}

void TetrisBoard::draw() {
    int y = 0; // nota y e x sono relativi alla window attuale
    int x = 0;
    for (int i = 0; i < block_height; i++) { // per ogni riga(std = 20)
        wmove(win, y, x);                    // mi sposto su nuova riga
        wprintw(win, "<!");                  // e scrivo

        for (int j = 0; j < block_width;
             j++) { // per ogni colonna (std = 10) (ogni colonna sono 2
                    // caratteri)
            wprintw(win, ". "); // carattere "·" non va
        }

        wprintw(win, "!>");
        // mi preparo a spostare cursore
        y++;
        x = 0;
    }
    wmove(win, y, x);
    wprintw(win, "  ");
    for (int i = 0; i < block_width; i++) {
        wprintw(win, "\\/"); // disegno il fondo
    }
    wrefresh(win);
}

bool TetrisBoard::addBlock(int y, int x) {
    x = x * 2 + this->border_width;
    if (y < this->height && x < this->width - this->border_width) {
        wmove(this->win, y, x);
        wprintw(win, "[]");
        return true;
    } else
        return false;
}

bool TetrisBoard::delBlock(int y, int x) {
    x = x * 2 + this->border_width;
    if (y < this->height && x < this->width - this->border_width) {
        wmove(this->win, y, x);
        wprintw(win, ". ");
        return true;
    } else
        return false;
}

bool TetrisBoard::isBlock(int y, int x) {
    x = x * 2 + this->border_width;
    if (y < this->height && x < this->width - this->border_width) {
        chtype found = this->getChar(y, x);
        if (found == '[')
            return true;
    }
    return false;
}

int TetrisBoard::lastYBlock() { return block_height; }

int TetrisBoard::lastXBlock() { return block_width; }

bool TetrisBoard::checkRow(int y) {
    bool full_row = true;
    int  i = this->border_width;
    for (int i = 0; i < this->block_width; i++) {
        bool found = this->isBlock(y, i);
        if (found == false)
            full_row = false;
    }
    return full_row;
}

int TetrisBoard::getInput() {
    chtype input = wgetch(win);

    return input;
}

int TetrisBoard::getTimeout() { return timeout; }

void TetrisBoard::setTimeout(int speed) { wtimeout(win, speed); }

int TetrisBoard::getBlockWidth() { return this->block_width; }

int TetrisBoard::getBlockHeight() { return this->block_height; }