/* 
 * File:   Farmacia.h
 * Author: j
 *
 * Created on May 30, 2013, 3:06 AM
 */

#ifndef FARMACIA_H
#define	FARMACIA_H

#include "Establecimiento.h"

using namespace std;

class Farmacia : public Establecimiento{
public:
    Farmacia(string dir, string nom, CoordUTM pos) : Establecimiento(dir, nom, pos){}
   
    virtual ~Farmacia();
private:

};

#endif	/* FARMACIA_H */

