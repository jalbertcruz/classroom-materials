/* 
 * File:   Pelota.cpp
 * Author: j
 * 
 * Created on May 28, 2013, 3:28 PM
 */
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Pelota.h"
#include "Jugador.h"

Pelota::Pelota(Jugador *j1, Jugador *j2) {
    this->j1 = j1;
    this->j2 = j2;
    
    std::srand(std::time(0));
    int r1 = std::rand();
    int r2 = std::rand();
    int r3 = std::rand();
    int r4 = std::rand();
    
    x = r1 % 100 - 1;
    y = r2 % 100 - 1;
    dx = r3 % 3 - 1;
    int arr[2] ={-1,1};
    dy = arr[r4 % 2];
}

Pelota::Pelota(const Pelota& orig) {
}

Pelota::~Pelota() {
}

