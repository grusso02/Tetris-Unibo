#include "../include/Game.hpp"
#include "../include/common_include.h" //per ncurses e altro
#include <ctime>
#include <iostream>
#include <limits.h>

#define START_Y 1
// #define COORX 30
#define BLOCKY 20
#define BLOCKX 10

// Game::Game(): tetris_board(), scores(), next_tetromino(), game_over(false),
// score(0),best_score(0){
/* // equivalentemente:
game_over = false;
score = 0;
best_score = 0;
*/
//}

Game::Game(int height, int width) { //(chiamato quando )serve a inizializzare tutti i parametri(=variabili) della classe

    // trovo dimensioni terminale
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // inizializzazione
    this->tetris_board = TetrisBoard(START_Y, max_x / 2, height, width, 500); // inizierà a metà schermo
    this->scores = Board(1, 3, 3, 17);       // altezza,larghezza,starty,startx
    this->next_tetromino = Board(6, 6, 5, 9);
    this->game_over = false;


    this->tetris_board.addBlock(10, 0);
    /*
    // test inserimento blocco e eliminaione riga
    this->tetris_board.addBlock(5, 0);
    this->tetris_board.addBlock(5, 1);
    this->tetris_board.addBlock(5, 2);
    this->tetris_board.addBlock(5, 3);
    this->tetris_board.addBlock(5, 4);
    this->tetris_board.addBlock(5, 5);
    this->tetris_board.addBlock(5, 6);
    this->tetris_board.addBlock(5, 7);
    this->tetris_board.addBlock(5, 8);
    this->tetris_board.addBlock(5, 9);
    this->tetris_board.addBlock(5, 10);
    this->tetris_board.addBlock(5, 11);
    this->tetris_board.addBlock(4, 4);
    // this->tetris_board.destroyRow(5);
    this->tetris_board.refresh();
    */

    // tetromino
    // next_tetromino
    this->score = 0;
    // this->best_score = apriFile(...);

    // inizializzo finestra "scores"
    scores.print(0, 0, "score: 0\n\nbest score: 0");
    scores.refresh();
    // inizializzo finestra "next_tetromino"
    next_tetromino.addBorder('T', 'T');
    next_tetromino.print(0, 0, "  NEXT:  ");
    next_tetromino.refresh();

    // controllo dimensioni stdscr (bozza)
    if ( enoughSpace(tetris_board.getHeight() + START_Y, tetris_board.getWidth() + (max_x / 2), max_y, max_x) == false) {
        clear();
        mvprintw(0, 0, "Allarga la finestra, grazie");
        refresh();
        return;
    } // nota:per adesso non considera dimensioni scores e next_tetromino;

    srandom(time(NULL));
    this->tetromino = Tetromino(tetris_board.getWidth());
    tetris_board.draw_piece(tetromino);
}

bool Game::enoughSpace(int needed_y, int needed_x, int max_y, int max_x) {
    if (needed_y > max_y || needed_x > max_x)
        return false;
    else
        return true;
}

Moves Game::processInput() {
    switch (tetris_board.getInput()) {
    case KEY_UP:
        return (ROTATE);
    case KEY_RIGHT:
        return (RIGHT);
    case KEY_LEFT:
        return (LEFT);
        /*     case 'p': {
                tetris_board.setTimeout(-1);
                while (tetris_board.getInput() != 'p')
                    ;
                tetris_board.setTimeout(tetris_board.getTimeout());
                break;
            } */
    case 'e':
        endGame();
        break;
    default:
        break;
    }
}

void Game::updateState() {
    Moves m = processInput();
    tetris_board.delete_piece(tetromino); // PRIMA di attuare modifiche cancello vecchio pezzo
    if(check_piece(tetromino) == false) // controlla se SOTTO c'è un pezzo
        tetromino.moveTurn(m);
    else{
        //passa al prossimo tetromino
    }
    checkCollision(); // corregge possibili valori illegali nella posizione tetromino
    tetris_board.draw_piece(tetromino);
}

void Game::checkCollision() {
    int* cells = tetromino.get_cells();
    int  x_max = 0;
    int  x_min = INT_MAX;

    for (int i = 0; i < 4; i++) {
        if (cells[2 * i] > x_max)
            x_max = cells[2 * i];
        if (cells[2 * i] < x_min)
            x_min = cells[2 * i];
        mvprintw(i, 5, "%d", cells[2 * i]);
    }

    mvprintw(0, 7, "%d", x_max);

    if ((x_max == 1 && tetromino.x == (tetromino.origin_x + 1)) ||
        (x_max == 2 && tetromino.x == tetromino.origin_x) ||
        (x_max == 3 && tetromino.x == (tetromino.origin_x - 1))) {
        tetromino.x--;
        tetromino.z -= 2;
    }

    mvprintw(1, 7, "%d", x_min);

    if ((x_min == 0 && tetromino.x == 0) || (x_min == 1 && tetromino.x == -1) || (x_min == 2 && tetromino.x == -2)) {
        tetromino.x++;
        tetromino.z += 2;
    }

    if (tetromino.type_name == I && x_min == 0 && tetromino.x == -1)
        tetromino.orientation = (tetromino.orientation + 1) % tetromino.symmetry;
}
/*
bool Game::check_block(int y, int x){
    if( tetris_board.isBlock(y, (x-2)*2) || y > tetris_board.lastYBlock() )
        return true;
    else
        return false;
}*/

bool Game::check_piece(Tetromino piece) {
    int* cells = piece.get_cells();
    int  x = 0;
    int  y = 0;
    bool flag_tetromino = false;
    bool flag_bottom = false;

    for (int i = 0; i < 4; i++) {
        x = cells[2 * i] * 2 + piece.origin_x;
        y = cells[2 * i + 1] + piece.origin_y;
        if(tetris_board.getChar(y+1,x+piece.z) == '[' && piece.belongs(y+1,x+piece.z)==false ) // controlla se ha pezzo SOTTO
            flag_tetromino = true;
        if(y+1 >= tetris_board.lastYBlock())
            flag_bottom = true;
    }
    return (flag_tetromino || flag_bottom);
}

bool Game::isOver() { return this->game_over; }

void Game::endGame() { this->game_over = true; }

void Game::redraw() { tetris_board.refresh(); }