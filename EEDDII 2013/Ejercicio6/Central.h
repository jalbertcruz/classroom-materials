/* 
 * File:   Central.h
 * Author: j
 *
 * Created on May 30, 2013, 9:40 AM
 */

#ifndef CENTRAL_H
#define	CENTRAL_H

#include <list>

#include "CentroRepetidor.h"

using namespace std;

class Central {
public:
    Central();
    Central(const Central& orig);
    virtual ~Central();

    void procesarSMS(int tDest, int tOrigen, string msg) {
        bool flag = true;
        for (list<CentroRepetidor*>::iterator it = repetidores.begin(); it != repetidores.end() && flag; ++it) {
            if (it->conectado(tDest)){
                flag = false;
                it->recepcionSMS(tDest, tOrigen, msg);
            }
        }
    }
private:

    list<CentroRepetidor*> repetidores;

};

#endif	/* CENTRAL_H */

