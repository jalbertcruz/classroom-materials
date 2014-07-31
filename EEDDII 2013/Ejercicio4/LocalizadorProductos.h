/* 
 * File:   LocalizadorProductos.h
 * Author: j
 *
 * Created on May 30, 2013, 5:42 AM
 */

#ifndef LOCALIZADORPRODUCTOS_H
#define	LOCALIZADORPRODUCTOS_H

#include <stdlib.h>

#include "CacheProductos.h"
#include "FicheroLocalProductos.h"
#include "ServidorRemotoProductos.h"
#include "Producto.h"
#include "ProductoCache.h"

using namespace std;

class LocalizadorProductos {
public:
    LocalizadorProductos();
    LocalizadorProductos(const LocalizadorProductos& orig);
    virtual ~LocalizadorProductos();

    Producto *buscarProducto(int codigo) {
        Producto *res = NULL;
        ProductoCache *pcache = NULL;
        pcache = cache.buscarProducto(codigo);
        if (pcache == NULL) {
            res = ficheroLocal.buscarProducto(codigo);
            if (res == NULL) {
                res = servidorRemoto.buscarProducto(codigo);
            }else{
                cache.annadirProducto(res);
            }
        }
        else {
            cache.actualizarFecha(pcache);
            res = pcache->getProducto();
        }
        if (res == NULL)
            throw "El producto no existe.";
        return res;
    }
    
private:
    ServidorRemotoProductos servidorRemoto;
    FicheroLocalProductos ficheroLocal;
    CacheProductos cache;
    
};

#endif	/* LOCALIZADORPRODUCTOS_H */

