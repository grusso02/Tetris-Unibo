#include "include/common_include.h"
#include <iostream>
#include <ncurses.h>
#include <sstream>

using namespace std;

#define N 20
#define HEIGHT N
#define WIDTH N // blocchi = 1/2 dell'altezza, MA blocchi = * 2 caratteri

using namespace std;

int main() {
    fstream fileClassifica;
    initscr();
    refresh();
    noecho();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    fileClassifica.open("file.txt", std::ios::app); /* Apertura del file */

    WINDOW* menuwin = newwin(0, xMax - 12, yMax - 8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    string choices[3] = {"Play", "Scores", "Exit"};
    int    choice;
    int    highlight = 0;

    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 1, 1, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch (choice) {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == 3)
                highlight = 2;
            break;
        default:
            break;
        }
        if (choice == ' ') {
            if (choices[highlight] == "Play") {
                clear();
                refresh();
                box(menuwin, 0, 0);
                wrefresh(menuwin);
                Game game(HEIGHT, WIDTH);

                while (!game.isOver()) {
                    game.updateState();
                    game.redraw();
                }
                fileClassifica << game.getScore() << ",";
            }
            if (choices[highlight] == "Scores") {
                clear();
                refresh();
                WINDOW* rank_board = newwin(20, 20, 0, (xMax / 2) - 10);
                box(rank_board, 0, 0);
                box(menuwin, 0, 0);

                string linea;
                char        c;
                int         i = 1;
                if (fileClassifica.is_open()) {
                    while (!fileClassifica.eof()) {
                        cout << "1" << endl;
                        fileClassifica.get(c);
                        if (c != ',')
                            linea += c;
                        else {
                            mvwprintw(rank_board, i, 1, linea.c_str());
                            linea = "";
                            i++;
                            wrefresh(rank_board);
                        }
                    }
                }
                wrefresh(rank_board);
                wrefresh(menuwin);
            }
            if (choices[highlight] == "Exit") {
                break;
            }
        }
    }

    endwin();
    fileClassifica.close();
    return 0;
}
