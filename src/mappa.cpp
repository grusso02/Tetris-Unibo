#include "../include/mappa.hpp"
#include "../include/common_include.h"

mappa::mappa(int ny, int nx, char chary, char charx) {
    WINDOW* win = newwin(ny, nx, 0, 0);
    box(win, chary, charx);
    wrefresh(win);
    while (true) {
    }
}