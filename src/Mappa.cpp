#include "../include/Mappa.hpp"
#include "../include/common_include.h"

Mappa::Mappa(int ny, int nx, char chary, char charx) {
    // inizializzo
    this->altezza = ny;
    this->larghezza = nx;
    WINDOW* window = newwin(ny, nx, 0, 0);
    this->win = window;
    // creo box
    box(win, chary, charx);
    wrefresh(win);
}