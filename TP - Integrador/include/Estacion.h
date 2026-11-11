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

    // Muestra los datos de la estación.
    void mostrarEstacion(ostream& salida) const
    {
        salida << "Codigo: " << codigo << endl;
        salida << "Nombre: " << nombre << endl;
        salida << "Barrio: " << barrio << endl;
        salida << "Capacidad de anclajes: " << capacidadAnclajes << endl;
        if (capacidadAnclajes > 0)
            salida << "Ocupacion: " << 100.0 * bicisDisponibles / capacidadAnclajes << "%" << endl;
        else
            salida << "Ocupacion: no disponible" << endl;
        salida << "Bicis disponibles: " << bicisDisponibles << endl;
    }
};

#endif
