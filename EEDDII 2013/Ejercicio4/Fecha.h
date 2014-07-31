/* 
 * File:   Fecha.h
 * Author: j
 *
 * Created on May 30, 2013, 5:41 AM
 */

#ifndef FECHA_H
#define	FECHA_H

class Fecha {
public:
    
    bool operator<(Fecha &f){
        return true;
    }

    bool operator>(Fecha &f){
        return true;
    }

    bool operator==(Fecha &f){
        return true;
    }
    
private:
    int d,m,a;
};

#endif	/* FECHA_H */

