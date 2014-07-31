/* 
 * File:   Movil.h
 * Author: j
 *
 * Created on May 30, 2013, 9:40 AM
 */

#ifndef MOVIL_H
#define	MOVIL_H

#include "CentroRepetidor.h"

using namespace std;

class Movil {
public:
    Movil(int tl, CentroRepetidor cent){
        tlf = tl;
        conexion = cent;
    }
    
    Movil(const Movil& orig);
    virtual ~Movil();
    
    int leerTlf(){
        return tlf;
    }
    
    void envioSMS(int tlfdest, string msg){
        conexion->envioSMS(tlfdest, msg);
    }
    
    void recepcionSMS(int tlfdest, string msg){
        
    }
    
    void cambioCentro(CentroRepetidor * nc){
        conexion = nc;
    }
    
private:
    int tlf;
    
    CentroRepetidor * conexion;
};

#endif	/* MOVIL_H */

