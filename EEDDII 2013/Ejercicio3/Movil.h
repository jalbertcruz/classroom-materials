/* 
 * File:   Movil.h
 * Author: j
 *
 * Created on May 30, 2013, 3:31 AM
 */

#ifndef MOVIL_H
#define	MOVIL_H

#include "CoordUTM.h"


class Movil {
public:
    Movil(int tf, CoordUTM pos){
        tfno = tf;
        posicion = pos;
    }
    
    CoordUTM leerPosicion(){
        return posicion;
    }
    
    void enviarSMS(int tfnoDest, string mensaje){
        
    }
    
    void recibirSMS(string texto, int tfnoOri){
        
    }
    
    int leerNo(){
        return tfno;
    }
    
    virtual ~Movil();
private:
    int tfno;
    CoordUTM posicion;

};

#endif	/* MOVIL_H */

