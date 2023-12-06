#include "include/common_include.h"
#include <iostream>

using namespace std;

int main() {
    cout << addition(1, 2) << endl;
    initscr(); /* Start curses mode 		  */

    Board primavesione(0, 0, 25, 100, '|', '-');
    primavesione.draw(2,2);
    while (true) {}
    // refresh(); /* update the real screen */
    // getch();   /* Wait for user input */

    endwin(); /* End curses mode		  */
    return 0;
}
