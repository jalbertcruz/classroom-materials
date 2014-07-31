/* 
 * File:   ControlPartido.h
 * Author: j
 *
 * Created on May 30, 2013, 8:05 AM
 */

#ifndef CONTROLPARTIDO_H
#define	CONTROLPARTIDO_H

#include <list>

#include "Equipo.h"
#include "Jugador.h"

using namespace std;

class ControlPartido {
public:
    ControlPartido();
    ControlPartido(const ControlPartido& orig);
    virtual ~ControlPartido();

    void canasta(int equipo, int numjugador, int puntos) {
        bool flag = true;
        for (list<Equipo*>::iterator it = equipos.begin(); it != equipos.end() && flag; ++it) {
            if (it->GetNo() == equipo) {
                it->canasta(numjugador, puntos);
                flag = false;
            }
        }
    }

    void personal(int equipo, int numjugador) {
        bool flag = true;
        for (list<Equipo*>::iterator it = equipos.begin(); it != equipos.end() && flag; ++it) {
            if (it->GetNo() == equipo) {
                it->personal(numjugador);
                flag = false;
            }
        }
    }

    bool expulsado(int equipo, int numjugador) {
        bool flag = true;
        for (list<Equipo*>::iterator it = equipos.begin(); it != equipos.end() && flag; ++it) {
            if (it->GetNo() == equipo) {
                return it->estaExpulsado(numjugador);
            }
        }
        throw "No existe el equipo.";
    }

    void cambio(int equipo, int numjugadorSale, int numJugadorEntra) {
        bool flag = true;
        for (list<Equipo*>::iterator it = equipos.begin(); it != equipos.end() && flag; ++it) {
            if (it->GetNo() == equipo) {
                it->cambio(numjugadorSale, numJugadorEntra);
            }
        }
    }

    Jugador * maximoEncestador() {
        list<Equipo*>::iterator it = equipos.begin();
        Jugador * result = it->maximoEncestador();
        ++it;
        for (; it != equipos.end(); ++it) {
            Jugador * j2 = it->maximoEncestador();
            if (j2->GetPuntos() > result->GetPuntos())
                result = j2;
        }

        return result;
    }

    int numExpulsados(int equipo) {
        bool flag = true;
        for (list<Equipo*>::iterator it = equipos.begin(); it != equipos.end() && flag; ++it) {
            if (it->GetNo() == equipo) {
                return it->numExpulsados();
            }
        }
        throw "No existe el equipo.";
    }

    Equipo * equipoGanador() {
        list<Equipo*>::iterator it = equipos.begin();
        Equipo * result = it;
        ++it;
        for (; it != equipos.end(); ++it) {
            if (it->GetPuntos() > result->GetPuntos())
                result = it;
        }

        return result;
    }

private:
    list<Equipo*> equipos;

};

#endif	/* CONTROLPARTIDO_H */

