#include "include/common_include.h"
#include <iostream>

using namespace std;

int main() {
    cout << addition(1, 2) << endl;
    initscr(); /* Start curses mode 		  */

    mappa primavesione(25, 100, '|', '-');
    // refresh(); /* update the real screen */
    // getch();   /* Wait for user input */

    endwin(); /* End curses mode		  */
    return 0;
}
