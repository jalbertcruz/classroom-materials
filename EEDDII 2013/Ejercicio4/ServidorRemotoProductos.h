/* 
 * File:   ServidorRemotoProductos.h
 * Author: j
 *
 * Created on May 30, 2013, 5:42 AM
 */

#ifndef SERVIDORREMOTOPRODUCTOS_H
#define	SERVIDORREMOTOPRODUCTOS_H

#include <list>

#include "Producto.h"

class ServidorRemotoProductos {
public:
    ServidorRemotoProductos();
    ServidorRemotoProductos(const ServidorRemotoProductos& orig);
    virtual ~ServidorRemotoProductos();
    
    Producto * buscarProducto(int codigo){
        
    }
    
private:
    list<Producto*> productos;
};

#endif	/* SERVIDORREMOTOPRODUCTOS_H */

