/* 
 * File:   Jugador.h
 * Author: j
 *
 * Created on May 28, 2013, 3:28 PM
 */

#ifndef JUGADOR_H
#define	JUGADOR_H

class Jugador {
public:
    Jugador(int x, int y, int l, int no);
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    
    int leerX(){
        return x;
    }
    int leerY(){
        return y;
    }
    int leerLongitud(){
        return longitud;
    }
    void izq(){
        if (x > 0)
            x -= 1;
    }
    void der() {
        if (x + longitud < 99)
            x += 1;
    }
private:
    int x, y, longitud, no;
};

#endif	/* JUGADOR_H */

