/* 
 * File:   CentroRepetidor.h
 * Author: j
 *
 * Created on May 30, 2013, 9:40 AM
 */

#ifndef CENTROREPETIDOR_H
#define	CENTROREPETIDOR_H

#include <list>
#include <stdlib.h>

#include "Central.h"
#include "Movil.h"

using namespace std;

class CentroRepetidor {
public:
    CentroRepetidor();
    CentroRepetidor(const CentroRepetidor& orig);
    virtual ~CentroRepetidor();

    void conectar(int tlf) {
         moviles.push_back(new Movil(tlf, this));
    }

    void desconectar(int tlf) {
        bool flag = true;
        Movil* res = NULL;
        for (list<Movil*>::iterator it = moviles.begin(); it != moviles.end() && flag; ++it) {
            if (it->leerTlf() == tlf) {
                res = it;
                flag = false;
            }
        }
        if (!flag)
            moviles.remove(res);
    }

    bool conectado(int tlf) {
        bool flag = false;
        for (list<Movil*>::iterator it = moviles.begin(); it != moviles.end() && !flag; ++it) {
            if (it->leerTlf() == tlf) {
                flag = true;
            }
        }
        return flag;
    }

    void envioSMS(int tlfdest, int tlfOrigen, string msg) {
        conexion->procesarSMS(tlfdest, tlfOrigen, msg);
    }

    void recepcionSMS(int tlfdest, string msg) {
        bool flag = true;
        for (list<Movil*>::iterator it = moviles.begin(); it != moviles.end() && flag; ++it) {
            if (it->leerTlf() == tlfdest) {
                it->recepcionSMS(tlfdest, msg)
                flag = false;
            }
        }
    }

private:

    Central * conexion;
    list<Movil*> moviles;

};

#endif	/* CENTROREPETIDOR_H */

