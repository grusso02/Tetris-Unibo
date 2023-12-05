#include "include/common_include.h"
#include <iostream>

using namespace std;

int main() {
    cout << addition(1, 2) << endl;
    initscr(); /* Start curses mode 		  */

    Mappa primavesione(25, 100, '|', '-');
    while (true) {
    }
    // refresh(); /* update the real screen */
    // getch();   /* Wait for user input */

    endwin(); /* End curses mode		  */
    return 0;
}
