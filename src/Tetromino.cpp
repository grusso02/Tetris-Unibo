#include "../include/Tetromino.hpp"

Tetromino::Tetromino(int screen_width) { get_piece(screen_width); }

void Tetromino::get_piece(int screen_width) {
    // per ogni tetromino: 
    // 1) salvo numero rotazioni possibili
    // 2) in base al tetromino, salvo rotazioni come posizioni in una griglia 4x4 (salvate in binario dentro un numero esadecimale) -> 1 esadecimale per ogni rotazione
    
    static int o_piece[] = {1, 0x5410};
    static int s_piece[] = {2, 0x4521, 0x9540};
    static int z_piece[] = {2, 0x6510, 0x8451};
    static int t_piece[] = {4, 0x4561, 0x5961, 0x9654, 0x4951};
    static int l_piece[] = {4, 0x4562, 0x59A1, 0x8654, 0x9510};
    static int j_piece[] = {4, 0x4560, 0x5921, 0xA654, 0x8951};
    static int i_piece[] = {2, 0x7654, 0xEA62};

    static int* piece_data[] = {
        o_piece, s_piece, z_piece, t_piece, l_piece, j_piece, i_piece,
    }; // salvo tutti pezzi in singolo array
    static int piece_data_len = 7;
    int        next_piece_random_index = random() % piece_data_len; // scelgo pezzo random
    type_name = static_cast<Piece>(next_piece_random_index);
    int* next_piece_data = piece_data[next_piece_random_index];


    origin_x = (screen_width - 4) / 2; // 4 = dimensione bordo
    origin_y = 0; // origin_y = 0; ?
    x = origin_x / 2;
    y = 0;
    z = 0;

    data = next_piece_data + 1; //salvo INDIRIZZO dell'esadecimale che rappresenta tetromino(e sua rotazione)
    // (+1 = escludo parte che rappresenta num rotazioni)
    symmetry = *next_piece_data;
    orientation = random() % symmetry;
}

int* Tetromino::get_cells() {
    // 8 celle = 8 num binari (di 2 cifre) = 4 coppie = le 4 caselle che il tetr. occupa nella griglia 4x4
    static int cells[8] = {};
    int        _data = *(data + orientation);

    for (int i = 0; i < 4; i++) {
        cells[2 * i] = ((int)(_data / pow(2, (4 * i))) % 4);
        cells[2 * i + 1] = y + ((int)(_data / pow(2, (4 * i + 2))) % 4);
    }

    return cells;
}

void Tetromino::move(Moves move) { // cambia le coordinate in base all'input (nota:possono essere illegali)
    switch (move) {
    case ROTATE:
        orientation = (orientation + 1) % symmetry;
        break;
    case RIGHT: {
        x = x + 1;
        z += 2;
        break;
    }
    case LEFT: {
        x = x - 1;
        z -= 2;
        break;
    }
    case DOWN:
        y = y + 1;
        break;
    default:
        break;
    }
}

void Tetromino::moveTurn(Moves move){
    this->move(DOWN);
    this->move(move);
}

bool Tetromino::belongs(int check_y, int check_x){
    int* cells = get_cells();
    int  x_i = 0;
    int  y_i = 0;
    bool flag = false;

    for (int i = 0; i < 4; i++) {
        x_i = cells[2 * i] * 2 + origin_x;
        y_i = cells[2 * i + 1] + origin_y;
        if( x_i + this->z == check_x && y_i == check_y) // controlla se appartiene -> nel caso ho risolto
            flag = true;
    }
    //return false;
    return flag;
}