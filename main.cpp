#include "include/common_include.h"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

int main() {
    initscr(); /* Start curses mode 		  */
    for (int i = 0; i < 10; i = i + 1) {
        clear();
        mvprintw(i, 0, "[][]");     /* Print Char		  */
        mvprintw(i + 1, 0, "[][]"); /* Print Char		  */
        sleep(1);
        refresh();
    }
    getch();
    endwin(); /* End curses mode		  */
    return 0;
}
