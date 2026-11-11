#ifndef ESTACION_H
#define ESTACION_H

#include <iostream>
#include <string>

using namespace std;

class Estacion
{
private:
    string codigo;
    string nombre;
    string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;

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
