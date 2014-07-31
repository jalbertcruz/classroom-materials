/* 
 * File:   CompanniaTelefonia.h
 * Author: j
 *
 * Created on May 30, 2013, 3:34 AM
 */

#ifndef COMPANNIATELEFONIA_H
#define	COMPANNIATELEFONIA_H

#include <list>

#include "Farmacia.h"
#include "Gasolinera.h"
#include "Movil.h"

using namespace std;

class CompanniaTelefonia {
public:
    CompanniaTelefonia();
    CompanniaTelefonia(const CompanniaTelefonia& orig);
    virtual ~CompanniaTelefonia();

    void envioSMS(int tfnDest, string texto) {

    }

    list<Farmacia> * buscaFarmacias(CoordUTM pos, int tfnoDest) {
        list<Farmacia> *res = new list<Farmacia>();
        int cant = 0;
        for (list<Farmacia>::iterator it = farmacias.begin(); it != farmacias.end(); ++it) {
            if (1 > pos.distancia(it->leerPosicion()) && cant < 4) {
                res->push_back(*it);
                cant++;
            }
        }
        return res;
    }

    /*
     * En gasolineras tiene que haber al menos una.
     */
    Gasolinera * buscaGasolineras(CoordUTM pos, int tfnoDest) {
        Gasolinera *res = gasolineras.front();
        for (list<Gasolinera>::iterator it = gasolineras.begin(); it != gasolineras.end(); ++it) {
            if (pos.distancia(res->leerPosicion() > pos.distancia(it->leerPosicion()))) {
                res = it;
            }
        }
        return new Gasolinera(*res);
    }

    void recepcionSMS(int tfnOri, string texto) {

        Movil * m = buscarMovil(tfnOri);

        if (m != NULL) {

            string msgRes = "";

            if (texto == "FARMACIA") {
                list<Farmacia> * res = buscaFarmacias(m->leerPosicion(), tfnOri);

                for (list<Farmacia>::iterator it = res.begin(); it != res.end(); ++it) {
                    msgRes += it->leerDireccion() + " | ";
                }

                delete res;

            } else if (texto == "GASOLINERA") {
                Gasolinera *res = buscaGasolineras(m->leerPosicion(), tfnOri);

                if (res != NULL) {
                    msgRes = res->leerDireccion();
                }

                delete res;
            }


            envioSMS(tfnOri, msgRes);

        }
    }

private:
    list<Farmacia> farmacias;
    list<Gasolinera> gasolineras;
    list<Movil> gestiona;

    Movil * buscarMovil(int tfnOri) {

        Movil * m = NULL;

        for (list<Movil>::iterator it = gestiona.begin(); it != gestiona.end() && m == NULL; ++it) {
            if (it->leerNo() == tfnOri) {
                m = it;
            }
        }
        return m;
    }
};

#endif	/* COMPANNIATELEFONIA_H */

