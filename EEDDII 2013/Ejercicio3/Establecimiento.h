/* 
 * File:   Establecimiento.h
 * Author: j
 *
 * Created on May 30, 2013, 3:02 AM
 */

#ifndef ESTABLECIMIENTO_H
#define	ESTABLECIMIENTO_H

#include "CoordUTM.h"

using namespace std;

class Establecimiento {
public:

    Establecimiento(string dir, string nom, CoordUTM pos) {
        direccion = dir;
        nombre = nom;
        posicion = pos;
    }

    string concatDir() {
        return direccion + " : " + posicion.ToString();
    }

    string leerDireccion() {
        return direccion;
    }

    CoordUTM leerPosicion() {
        return posicion;
    }


    virtual ~Establecimiento();
private:

protected:
    string direccion, nombre;
    CoordUTM posicion;
};

#endif	/* ESTABLECIMIENTO_H */

