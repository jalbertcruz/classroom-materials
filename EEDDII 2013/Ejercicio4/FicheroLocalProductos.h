/* 
 * File:   FicheroLocalProductos.h
 * Author: j
 *
 * Created on May 30, 2013, 5:42 AM
 */

#ifndef FICHEROLOCALPRODUCTOS_H
#define	FICHEROLOCALPRODUCTOS_H

#include "Producto.h"

class FicheroLocalProductos {
public:
    FicheroLocalProductos();
    FicheroLocalProductos(const FicheroLocalProductos& orig);
    virtual ~FicheroLocalProductos();

    Producto * buscarProducto(int codigo) {

    }

private:

};

#endif	/* FICHEROLOCALPRODUCTOS_H */

