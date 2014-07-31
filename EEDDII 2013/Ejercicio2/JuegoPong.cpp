/* 
 * File:   JuegoPong.cpp
 * Author: j
 * 
 * Created on May 28, 2013, 3:27 PM
 */

#include "JuegoPong.h"

JuegoPong::JuegoPong() {
    primeraVez = true;
}

JuegoPong::JuegoPong(const JuegoPong& orig) {
}

JuegoPong::~JuegoPong() {
    // lo que debe hacerse segun este destructor es crear los objetos en el constructor... pero el enunciado del ejercicio dice que sea en el bucle.
    delete p;
    delete j1;
    delete j2;
}

