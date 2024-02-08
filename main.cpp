#include "include/Game.hpp"
#include <fstream>
#include <iostream>
#include <ncurses.h>

using namespace std;

#define N 20
#define HEIGHT N
#define WIDTH N // blocchi = 1/2 dell'altezza, MA blocchi = * 2 caratteri

#define NUM_MAX 10

int compare(const void* a, const void* b) { return (*(int*)b - *(int*)a); }

using namespace std;

int main() {
    fstream fileClassifica;
    initscr();
    refresh();
    noecho();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

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
                fileClassifica.open("file.txt", std::ios::app);
                fileClassifica << game.getScore() << ",";
                fileClassifica.close();
            }
            if (choices[highlight] == "Scores") {
                clear();
                refresh();
                WINDOW* rank_board = newwin(20, 20, 0, (xMax / 2) - 10);
                box(rank_board, 0, 0);
                box(menuwin, 0, 0);

                mvwprintw(rank_board, 1, 5, "CLASSIFICA");

                fileClassifica.open("file.txt", std::ios::in);
                int    numbers[NUM_MAX] = {};
                string linea;
                int    i = 0;
                while (getline(fileClassifica, linea, ',') && i < 10) {
                    numbers[i] = stoi(linea);
                    i++;
                }

                qsort(numbers, NUM_MAX, sizeof(int), compare);

                for (int j = 0; j < NUM_MAX; j++) {
                    mvwprintw(rank_board, j + 2, 9, "%d", numbers[j]);
                }

                wrefresh(rank_board);
                wrefresh(menuwin);
                fileClassifica.close();
            }
            if (choices[highlight] == "Exit") {
                break;
            }
        }
    }
    endwin();
    return 0;
}
