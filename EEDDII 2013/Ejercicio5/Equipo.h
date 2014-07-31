/* 
 * File:   Equipo.h
 * Author: j
 *
 * Created on May 30, 2013, 8:06 AM
 */

#ifndef EQUIPO_H
#define	EQUIPO_H

#include <stdlib.h>
#include <list>
#include "Jugador.h"

using namespace std;

class Equipo {
public:
    Equipo();
    Equipo(const Equipo& orig);
    virtual ~Equipo();

    int GetNo() const {
        return no;
    }

    string GetPais() const {
        return pais;
    }

    int GetPuntos() const {
        return puntos;
    }

    void canasta(int numjugador, int puntos) {
        bool flag = true;
        for (list<Jugador*>::iterator it = enJuego.begin(); it != enJuego.end() && flag; ++it) {
            if (it->GetNum() == numjugador) {
                flag = false;
                it->aumentarPuntos(puntos);
                this->puntos += puntos;
            }
        }
        if (flag)
            throw "El jugador no está en juego.";
    }

    void personal(int numjugador) {
        bool flag = true;
        for (list<Jugador*>::iterator it = enJuego.begin(); it != enJuego.end() && flag; ++it) {
            if (it->GetNum() == numjugador) {
                flag = false;
                it->aumentarFaltas();
                if (it->GetPersonales() == 5)
                    throw "El jugador ya no puede seguir jugando, maximo numero de faltas alcanzadas.";
            }
        }
        if (flag)
            throw "El jugador no está en juego.";
    }

    bool estaExpulsado(int numjugador) {
        bool flag = true;
        bool res = false;

        for (list<Jugador*>::iterator it = enJuego.begin(); it != enJuego.end() && flag; ++it) {
            if (it->GetNum() == numjugador) {
                flag = false;
                if (it->GetPersonales() == 5)
                    res = true;
            }
        }

        for (list<Jugador*>::iterator it = convocados.begin(); it != convocados.end() && flag; ++it) {
            if (it->GetNum() == numjugador) {
                flag = false;
                if (it->GetPersonales() == 5)
                    res = true;
            }
        }

        if (flag)
            throw "El jugador no está en juego.";
        else
            return res;
    }

    void cambio(int numjugadorSale, int numJugadorEntra) {
        bool flag = true;
        for (list<Jugador*>::iterator it = enJuego.begin(); it != enJuego.end() && flag; ++it) {
            if (it->GetNum() == numJugadorEntra) {
                flag = false;
            }
        }
        if (flag)
            throw "El jugador que entra está en juego.";

        flag = true;
        Jugador * jentra = NULL;

        for (list<Jugador*>::iterator it = convocados.begin(); it != convocados.end() && flag; ++it) {
            if (it->GetNum() == numJugadorEntra) {
                flag = false;
                jentra = it;
            }
        }
        if (flag)
            throw "El jugador que entra no es de los que están fuera de pista.";

        if (estaExpulsado(numJugadorEntra))
            throw "El jugador que entra está expulsado.";

        flag = true;
        Jugador* jsale = NULL;
        for (list<Jugador*>::iterator it = enJuego.begin(); it != enJuego.end() && flag; ++it) {
            if (it->GetNum() == numjugadorSale) {
                flag = false;
                jsale = it;
            }
        }
        if (flag)
            throw "El jugador que sale no está en juego.";

        enJuego.remove(jsale);
        enJuego.push_back(jentra);
        convocados.remove(jentra);
        convocados.push_back(jsale);

    }

    Jugador* maximoEncestador() {
        list<Jugador*>::iterator it = enJuego.begin();
        Jugador* result = it;
        ++it;
        for (; it != enJuego.end(); ++it) {
            if (result->GetPuntos() < it->GetPuntos())
                result = it;
        }

        for (list<Jugador*>::iterator it = convocados.begin(); it != convocados.end(); ++it) {
            if (result->GetPuntos() < it->GetPuntos())
                result = it;
        }
    }

    int numExpulsados() {
        int result = 0;
        for (list<Jugador*>::iterator it = convocados.begin(); it != convocados.end(); ++it) {
            if (it->GetPersonales() == 5)
                result++;
        }
        return result;
    }

private:
    string pais;
    int puntos;

    list<Jugador*> enJuego;
    list<Jugador*> convocados;

    int no;

};

#endif	/* EQUIPO_H */

