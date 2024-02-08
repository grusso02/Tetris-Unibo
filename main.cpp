#include "include/common_include.h"
#include <iostream>

using namespace std;

#define N 20
#define HEIGHT N
#define WIDTH N // blocchi = 1/2 dell'altezza, MA blocchi = * 2 caratteri

using namespace std;

int main() {
    initscr();
    refresh();
    noecho();
    curs_set(0);


    *WINDOW = win;

    int y = 0;
    int selected = -1;
    char pressed = NULL;

    std::string choices[3] = {"START","BEST SCOES","EXIT"};

    while(selected != -1){

        for(int i=0;i<2;i++){
            if(i == y)
                wattron(win,A_STANDOUT);
            print(i+1,0,choices[i].c_str());
            wattroff(win,A_STANDOUT);
        }
        wrefresh();
        // cambio puntatore
        pressed = wgetch(win);
        switch(pressed){
            case KEY_DOWN:
                if(y-1 >= 0)
                    y--;
                break;
            case KEY_UP:
                if(y+1 >= 0)
                    y++;
            case KEY_ENTER:
                selected = y;
                break;
        }
    }
    return selected;

















    //Game game(HEIGHT, WIDTH);
    Menu m(0,0,10,100);
    while(m.getInput()){
    }
        

    /*while (!game.isOver()) {

        //game.updateState();
        //game.redraw();
    }*/
    endwin();
    cout << "Hai perso" << endl;
    return 0;
}
