/* 
 * File:   CoordUTM.h
 * Author: j
 *
 * Created on May 30, 2013, 2:55 AM
 */

#ifndef COORDUTM_H
#define	COORDUTM_H

#include <cmath>
#include <sstream>

using namespace std;

class CoordUTM {
public:
    CoordUTM(double x, double y){
        this->x = x;
        this->y = y;
    }
    double distancia(CoordUTM pos){
        return sqrt(pow(pos.x - x, 2) + pow(pos.y - y, 2));
    }
    virtual ~CoordUTM();
    
    string ToString(){
        std::ostringstream xs;
        xs << x;
        std::ostringstream xy;
        xy << y;
        return "(" + xs.str() + ", " + xy.str() + ")";
    }
    
private:
    double x, y;

};

#endif	/* COORDUTM_H */

