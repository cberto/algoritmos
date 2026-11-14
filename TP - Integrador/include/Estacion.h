#ifndef ESTACION_H
#define ESTACION_H

#include <iostream>
#include <string>

#include "Estructuras.h"

using namespace std;

class Estacion {
    private:
        string codigo;
        string nombre;
        string barrio;
        int capacidadAnclajes;
        int bicisDisponibles;

    public:
        Cola<int> espera;
    Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int bicisDisponibles) {
        this->codigo = codigo;
        this->nombre = nombre;
        this->barrio = barrio;
        this->capacidadAnclajes = capacidadAnclajes;
        this->bicisDisponibles = bicisDisponibles;
    }
   
    string getCodigo() const {
        return codigo;
    }

    int getCapacidad() const {
        return capacidadAnclajes;
    }

    int getDisponible() const {
        return bicisDisponibles;
    }

    void restarDisponible() {
        --bicisDisponibles;
    }

    bool sumarDisponible() {
        if (bicisDisponibles >= capacidadAnclajes) return false;
        ++bicisDisponibles;
        return true;
    }
 
    void mostrarEstacion() const{
        cout << " | Codigo: " << codigo << endl
             << " | Nombre: " << nombre << endl
             << " | Barrio: " << barrio << endl
             << " | Capacidad de anclajes: " << capacidadAnclajes << endl
             << " | Ocupacion: " << 100.0 * bicisDisponibles / capacidadAnclajes << "%" << endl
             << " | Personas en espera: " << espera.cantidad() << endl
             << " | Bicis disponibles: " << bicisDisponibles << endl;
    }
};
#endif
