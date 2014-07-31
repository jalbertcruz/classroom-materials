/* 
 * File:   Pelota.h
 * Author: j
 *
 * Created on May 28, 2013, 3:28 PM
 */

#ifndef PELOTA_H
#define	PELOTA_H

#include "Jugador.h"


class Pelota {
public:
    Pelota(Jugador *j1, Jugador *j2);
    Pelota(const Pelota& orig);
    virtual ~Pelota();
    
    void actualizaPosicion(){
        x += dx;
        y += dy;
        
        if (x == 0 || x == 99)
            dx = -dx;

        bool tocandoj1 = false;
        if (y == j1->leerY() && x >= j1->leerX() && x <= j1->leerX() + j1->leerLongitud())
            tocandoj1 = true;

        bool tocandoj2 = false;
        if (y == j2->leerY() && x >= j1->leerX() && x <= j1->leerX() + j1->leerLongitud())
            tocandoj2 = true;

        if (tocandoj1 || tocandoj2) {
            dy = -dy;
            dx = -dx;
        }
    }
    
    bool fueraJugador1(){
        return y > 99;
    }

    bool fueraJugador2(){
        return y < 0;
    }
    
private:
    int x, y, dx, dy;
    Jugador *j1, *j2;

};

#endif	/* PELOTA_H */

