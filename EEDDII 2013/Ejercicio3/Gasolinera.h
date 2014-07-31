/* 
 * File:   Gasolinera.h
 * Author: j
 *
 * Created on May 30, 2013, 3:29 AM
 */

#ifndef GASOLINERA_H
#define	GASOLINERA_H

#include "Establecimiento.h"

using namespace std;

class Gasolinera : public Establecimiento{
public:
    Gasolinera(string dir, string nom, CoordUTM pos) : Establecimiento(dir, nom, pos){}
    
    virtual ~Gasolinera();
private:

};

#endif	/* GASOLINERA_H */

