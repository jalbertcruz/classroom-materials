/* 
 * File:   Jugador.cpp
 * Author: j
 * 
 * Created on May 28, 2013, 3:28 PM
 */

#include "Jugador.h"

Jugador::Jugador(int x, int y, int l, int no) {
    this->x = x;
    this->y = y;
    this->longitud = l;
    this->no = no;
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

