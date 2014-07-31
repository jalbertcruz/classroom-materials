/* 
 * File:   ProductoCache.h
 * Author: j
 *
 * Created on May 30, 2013, 5:41 AM
 */

#ifndef PRODUCTOCACHE_H
#define	PRODUCTOCACHE_H

#include "Producto.h"
#include "Fecha.h"

class ProductoCache {
public:

    ProductoCache(Producto * p) {
        producto = p;
        actualizarFecha();
    }

    ProductoCache(const ProductoCache& orig);
    virtual ~ProductoCache();

    void actualizarFecha() {
    }

    Producto* getProducto() const {
        return producto;
    }

    Fecha getUltimoAcceso() const {
        return ultimoAcceso;
    }


private:

    Producto * producto;
    Fecha ultimoAcceso;

};

#endif	/* PRODUCTOCACHE_H */

