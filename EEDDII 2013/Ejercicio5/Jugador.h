/* 
 * File:   Jugador.h
 * Author: j
 *
 * Created on May 30, 2013, 8:06 AM
 */

#ifndef JUGADOR_H
#define	JUGADOR_H

using namespace std;

class Jugador {
public:
    Jugador();
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    
    int GetEdad() const {
        return edad;
    }

    void SetEdad(int edad) {
        this->edad = edad;
    }

    string GetNombre() const {
        return nombre;
    }

    void SetNombre(string nombre) {
        this->nombre = nombre;
    }

    int GetNum() const {
        return num;
    }

    void SetNum(int num) {
        this->num = num;
    }

    int GetPersonales() const {
        return personales;
    }

    void SetPersonales(int personales) {
        this->personales = personales;
    }

    int GetPuntos() const {
        return puntos;
    }

    void SetPuntos(int puntos) {
        this->puntos = puntos;
    }

    void aumentarPuntos(int puntos) {
        this->puntos += puntos;
    }

    void aumentarFaltas() {
        this->personales ++;
    }
    
private:
    string nombre;
    int edad, num, personales, puntos;
};

#endif	/* JUGADOR_H */

