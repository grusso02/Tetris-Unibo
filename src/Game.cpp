#include "../include/Game.hpp"
#include <unistd.h>

Game::Game(int height,
           int width) { //(chiamato quando )serve a inizializzare
                        // tutti i parametri(=variabili) della classe
    srandom(time(NULL));

    // trovo dimensioni terminale
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // controllo dimensioni stdscr (bozza)
    if (enoughSpace(tetris_board.getHeight() + START_Y,
                    tetris_board.getWidth() + (max_x / 2), max_y,
                    max_x) == false) {
        clear();
        mvprintw(0, 0, "Allarga la finestra, grazie");
        refresh();
        return;
    } // nota:per adesso non considera dimensioni scores e next_tetromino;

    // inizializzazione
    this->score = 0;
    this->tetris_board = TetrisBoard(START_Y, max_x / 2, height, width,
                                     500); // inizierà a metà schermo
    this->score_board = Scoreboard(17, 3, 3);
    score_board.initialize(score);

    // this->scores = Board(1, 3, 3, 17);     // altezza,larghezza,starty,startx
    this->window_next_tetromino = Board(6, 6, 5, 9);

    this->tetromino = Tetromino(tetris_board.getWidth());
    this->next_tetromino = Tetromino(tetris_board.getWidth());

    this->game_over = false;

    // inizializzo finestra "next_tetromino"
    draw_next_piece(next_tetromino);
    window_next_tetromino.refresh();

    draw_piece(tetromino);
}

Game::~Game() {
    score_board.print(2, 0, "Game Over!");
    redraw();
}

bool Game::enoughSpace(int needed_y, int needed_x, int max_y, int max_x) {
    if (needed_y > max_y || needed_x > max_x)
        return false;
    else
        return true;
}

Moves Game::processInput() {
    switch (tetris_board.getInput()) {
    case ERR:
        return (DOWN);
    case KEY_UP:
        return (ROTATE);
    case KEY_RIGHT:
        return (RIGHT);
    case KEY_LEFT:
        return (LEFT);
    case ' ':
        return (FALL);
    case 'e':
        endGame();
        break;
    default:
        break;
    }
    return (ZERO);
}

void Game::updateState() {
    Moves m = processInput();

    if (check_floor_and_piece() ==
        false) { // controlla se SOTTO c'è un pezzo o il fondo
        delete_piece(
            tetromino); // PRIMA di attuare modifiche cancello vecchio pezzo
        if (m == FALL)
            while (check_floor_and_piece() != true)
                tetromino.move(DOWN);
        else
            tetromino.move(m);
    } else {
        this->tetromino = next_tetromino;
        this->next_tetromino = Tetromino(tetris_board.getWidth());
        window_next_tetromino.clear();
        draw_next_piece(next_tetromino);
        window_next_tetromino.refresh();
    }

    checkCollision(
        m); // corregge possibili valori illegali nella posizione tetromino
    draw_piece(tetromino);

    // eliminare righe piene(beta)
    delete_piece(tetromino);
    destroyFullRows();
    draw_piece(tetromino);
}

void Game::checkCollision(Moves m) { // controlla se ATTUALMENTE coordinate
                                     // tetromino collidono a destra o sinistra
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

    if ((x_max == 1 && tetromino.x == (tetromino.origin_x)) ||
        (x_max == 2 && tetromino.x == tetromino.origin_x - 1) ||
        (x_max == 3 && tetromino.x == (tetromino.origin_x - 2))) {
        tetromino.x--;
        tetromino.z -= 2;
    }

    mvprintw(1, 7, "%d", x_min);

    if ((x_min == 0 && tetromino.x == 0) || (x_min == 1 && tetromino.x == -1) ||
        (x_min == 2 && tetromino.x == -2)) {
        tetromino.x++;
        tetromino.z += 2;
    }

    if (tetromino.type_name == I && x_min == 0 && tetromino.x == -1)
        tetromino.orientation =
            (tetromino.orientation + 1) % tetromino.symmetry;

    for (int i = 0; i < 4; i++) {
        int x = cells[2 * i] * 2 + tetromino.origin_x;
        int y = cells[2 * i + 1] + tetromino.origin_y;

        // Collisione tetromino destra
        if (m == RIGHT && tetris_board.getChar(y, x + tetromino.z) == '[') {
            tetromino.x--;
            tetromino.z -= 2;
        }

        // Collisione tetromino sinistra
        if (m == LEFT && tetris_board.getChar(y, x + tetromino.z + 1) == ']') {
            tetromino.x++;
            tetromino.z += 2;
        }
    }
}

bool Game::check_floor_and_piece() {
    int* cells = tetromino.get_cells();
    int  x = 0;
    int  y = 0;
    bool flag_tetromino = false;
    bool flag_bottom = false;

    for (int i = 0; i < 4; i++) {
        x = cells[2 * i] * 2 + tetromino.origin_x;
        y = cells[2 * i + 1] + tetromino.origin_y;
        if (tetris_board.getChar(y + 1, x + tetromino.z) == '[' &&
            tetromino.belongs(y + 1, x + tetromino.z) ==
                false) // controlla se ha pezzo SOTTO
        {
            if (tetromino.origin_y == tetromino.y)
                endGame();
            flag_tetromino = true;
        }
        if (y + 1 >= tetris_board.lastYBlock())
            flag_bottom = true;
    }
    return (flag_tetromino || flag_bottom);
}

void Game::draw_next_piece(Tetromino piece) {
    int* cells = piece.get_cells();
    int  print_x = 0;
    int  print_y = 0;

    for (int i = 0; i < 4; i++) {
        print_x = cells[2 * i] * 2;
        print_y = cells[2 * i + 1];
        window_next_tetromino.print(print_y, print_x, "[]");
    }
}

void Game::draw_piece(Tetromino piece) {
    int* cells = piece.get_cells();
    int  print_x = 0;
    int  print_y = 0;

    for (int i = 0; i < 4; i++) {
        print_x = cells[2 * i] * 2 + piece.origin_x;
        print_y = cells[2 * i + 1] + piece.origin_y;
        tetris_board.print(print_y, print_x + piece.z, "[]");
    }
}

void Game::delete_piece(Tetromino piece) {
    int* cells = piece.get_cells();
    int  print_x = 0;
    int  print_y = 0;

    for (int i = 0; i < 4; i++) {
        print_x = cells[2 * i] * 2 + piece.origin_x;
        print_y = cells[2 * i + 1] + piece.origin_y;
        tetris_board.print(print_y, print_x + piece.z, ". ");
    }
}

void Game::destroyFullRows() {
    int tot_rows = 0;
    int i = tetris_board.lastYBlock();
    while (i >= 0) {
        if (tetris_board.checkRow(i) == true) {
            destroyRow(i); // se piena cancella e fa cadere tutto quello sopra
                           // di una riga
            tot_rows++;
        } else
            i--;
    }
    this->score += tot_rows * tot_rows; // = 1, 4, 9, 16
    score_board.updateScore(score);
}

bool Game::isOver() { return this->game_over; }

void Game::endGame() { this->game_over = true; }

void Game::redraw() {
    tetris_board.refresh();
    score_board.refresh();
}

int Game::getScore() { return score; }

bool Game::destroyRow(int y) {
    if (tetris_board.checkRow(y) == true) {
        // distruggo riga
        for (int i = 0; i < tetris_board.getBlockWidth(); i++)
            tetris_board.delBlock(y, i);
        // causo discesa altri elementi
        for (int i = y - 1; i >= 0; i--) { // vado verso l'alto
            for (int j = 0; j < tetris_board.getBlockWidth(); j++)
                if (tetris_board.isBlock(i, j)) {
                    tetris_board.delBlock(i, j);
                    tetris_board.addBlock(i + 1, j); // aggiungo più in basso
                }
        }
        return true;
    } else
        return false;
}