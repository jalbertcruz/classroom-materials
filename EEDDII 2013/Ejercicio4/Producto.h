/* 
 * File:   Producto.h
 * Author: j
 *
 * Created on May 30, 2013, 5:41 AM
 */

#ifndef PRODUCTO_H
#define	PRODUCTO_H

#include <string>

using namespace std;

class Producto {
public:
    
    virtual ~Producto();
    
    int GetCodigo() const {
        return codigo;
    }

    void SetCodigo(int codigo) {
        this->codigo = codigo;
    }

private:
    
    double precio;
    int codigo;
    string desc;

};

#endif	/* PRODUCTO_H */

