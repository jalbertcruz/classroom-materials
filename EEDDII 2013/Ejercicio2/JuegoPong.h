/* 
 * File:   JuegoPong.h
 * Author: j
 *
 * Created on May 28, 2013, 3:27 PM
 */

#ifndef JUEGOPONG_H
#define	JUEGOPONG_H

#include "Jugador.h"
#include "Pelota.h"


class JuegoPong {
public:
    JuegoPong();
    JuegoPong(const JuegoPong& orig);
    virtual ~JuegoPong();
    
    void teclaIzqJug1(){
        j1->izq();
    }
    void teclaDerJug1(){
        j1->der();
    }
    void teclaIzqJug2(){
        j2->izq();
    }
    void teclaDerJug2(){
        j2->der();
    }
    
    void bucleJuego(){
        if (primeraVez) {
            j1 = new Jugador(49, 99, 10, 1);
            j2 = new Jugador(49, 0, 10, 2);
            p = new Pelota(j1, j2);
            primeraVez = false;
        }else{
            // De alguna manera se ejecuta esto cada 1 segundo...
            p->actualizaPosicion();
        }
    }
    
private:
    
    Pelota *p;
    Jugador *j1, *j2;
    bool primeraVez;

};

#endif	/* JUEGOPONG_H */

