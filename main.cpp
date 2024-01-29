#include "include/common_include.h"
#include <iostream>

using namespace std;

#define N 20
#define HEIGHT N
#define WIDTH N * 1.5

using namespace std;

int main() {
    initscr();
    refresh();
    noecho();
    curs_set(0);

    Game game(HEIGHT, WIDTH);

    while (!game.isOver()) {
        game.processInput();
        game.updateState();
        game.redraw();
    }

    endwin();
    return 0;
}
