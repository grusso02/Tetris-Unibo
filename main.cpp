#include "include/common_include.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

int main() {
    cout << addition(1, 2) << endl;
    initscr();                     /* Start curses mode 		  */
    printw("Hello World!!!! !!!"); /* Print Hello World		  */
    refresh();                     /* Print it on to the real screen */
    getch();                       /* Wait for user input */
    endwin();                      /* End curses mode		  */
    return 0;
}
