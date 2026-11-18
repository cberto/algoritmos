#ifndef ESTACION_H
#define ESTACION_H

#include <iostream>
#include <string>
#include "Cola.h"

using namespace std;

class Estacion
{
private:
    string codigo;
    string nombre;
    string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;
    Cola<int> espera;

public:
    // Crea una estación vacía para permitir su almacenamiento en la tabla.
    Estacion()
    {
        codigo = "";
        nombre = "";
        barrio = "";
        capacidadAnclajes = 0;
        bicisDisponibles = 0;
    }

    // Crea una estación con los datos recibidos.
    Estacion(string codigoNuevo, string nombreNuevo, string barrioNuevo,
             int capacidadNueva, int disponiblesNuevas)
    {
        codigo = codigoNuevo;
        nombre = nombreNuevo;
        barrio = barrioNuevo;
        capacidadAnclajes = capacidadNueva;
        bicisDisponibles = disponiblesNuevas;
    }

    // Devuelve el código de la estación.
    string getCodigo()
    {
        return codigo;
    }

    // Devuelve la capacidad de anclajes.
    int getCapacidadAnclajes()
    {
        return capacidadAnclajes;
    }

    // Devuelve la cantidad de bicicletas disponibles.
    int getBicisDisponibles()
    {
        return bicisDisponibles;
    }

    // Retira una bicicleta disponible de la estación.
    bool retirarBicicleta()
    {
        if (bicisDisponibles == 0)
            return false;
        --bicisDisponibles;
        return true;
    }

    // Recibe una bicicleta si queda capacidad libre.
    bool recibirBicicleta()
    {
        if (bicisDisponibles >= capacidadAnclajes)
            return false;
        ++bicisDisponibles;
        return true;
    }

    // Indica si no hay usuarios esperando una bicicleta.
    bool colaVaciaDeEspera() const
    {
        return espera.vacia();
    }

    // Agrega el DNI del usuario al final de la cola de espera.
    void encolarEspera(int dniUsuario)
    {
        espera.encolar(dniUsuario);
    }

    // Quita y devuelve el DNI del primer usuario en espera.
    bool desencolarEspera(int& dniUsuario)
    {
        return espera.desencolar(dniUsuario);
    }

    // Muestra los datos de la estación.
    void mostrarEstacion() const
    {
        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Barrio: " << barrio << endl;
        cout << "Capacidad de anclajes: " << capacidadAnclajes << endl;
        if (capacidadAnclajes > 0)
            cout << "Ocupacion: " << 100.0 * bicisDisponibles / capacidadAnclajes << "%" << endl;
        else
            cout << "Ocupacion: no disponible" << endl;
        cout << "Bicis disponibles: " << bicisDisponibles << endl;
    }
};

#endif
