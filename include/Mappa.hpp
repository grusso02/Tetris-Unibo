
#pragma once // per evitare ridefinizione della classe mappa -> errore
             // compilazione
#include <ncurses.h>

class Mappa {
  private:
    int     altezza, larghezza;
    WINDOW* win;

  public:
    Mappa(int ny, int nx, char chary, char charx);
};