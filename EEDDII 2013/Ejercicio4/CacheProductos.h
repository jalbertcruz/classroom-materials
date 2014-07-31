/* 
 * File:   CacheProductos.h
 * Author: j
 *
 * Created on May 30, 2013, 5:42 AM
 */

#ifndef CACHEPRODUCTOS_H
#define	CACHEPRODUCTOS_H

#include <stdlib.h>
#include <map>
#include <list>

#include "Producto.h"
#include "Fecha.h"
#include "ProductoCache.h"

using namespace std;

class CacheProductos {
public:
    CacheProductos();
    CacheProductos(const CacheProductos& orig);
    virtual ~CacheProductos();
    
    ProductoCache *buscarProducto(int codigo){
        ProductoCache *res = NULL;
        map<int,ProductoCache*>::iterator it = itemsPorCodigo.find(codigo);
        if (it != itemsPorCodigo.end())
            res = it->second;
        return res;
    }
    
    void annadirProducto(Producto *prod){
        ProductoCache * padd = new ProductoCache(prod);
        if (itemsPorCodigo.size() == 1000){
            map<Fecha, ProductoCache*>::iterator it = itemsPorFecha.begin();
            Fecha f = it->first;
            ++it;
            for(; it !=  itemsPorFecha.end(); ++it ){
                if (it->first < f){
                    f = it->first;
                }
            }
            itemsPorCodigo.erase(itemsPorFecha[f]->getProducto()->GetCodigo());
            itemsPorFecha.erase(f);
        }
        
        itemsPorCodigo[padd->getProducto()->GetCodigo()] = padd;
        itemsPorFecha[padd->getUltimoAcceso()] = padd;
    }
    
    void actualizarFecha(ProductoCache *pcache){
        itemsPorFecha.erase(pcache->getUltimoAcceso());
        pcache->actualizarFecha();
        itemsPorFecha[pcache->getUltimoAcceso()] = pcache;
    }
    
private:
    map<int,ProductoCache*> itemsPorCodigo;
    map<Fecha, ProductoCache*> itemsPorFecha;
    
};

#endif	/* CACHEPRODUCTOS_H */

