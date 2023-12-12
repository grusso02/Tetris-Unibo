#include "include/common_include.h"
#include <iostream>
#define HEIGHT 50
#define WIDTH 50

using namespace std;


int main() {
    cout << addition(1, 2) << endl;
    initscr(); // Start curses mode

    TetrisBoard test(0, 0);
    while(true){}
    // getch();   // Wait for user input

    endwin(); //End curses mode
    return 0;
}
