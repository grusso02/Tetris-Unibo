#include "include/common_include.h"
#include <iostream>
#define HEIGHT 50
#define WIDTH 50

using namespace std;


int main() {

    initscr(); // Start curses mode

    Game game1(0);

    while( game1.isOver() == false ){
        // game1.processInput(); // riceve l'input dall'utente(se inserito)
        // game1.updateState(); // agisce in base all'input ricevuto
        // game1.redraw(); // disegna cambiamenti sulla window
    }

    endwin(); //End curses mode
    return 0;
}
