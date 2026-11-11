#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "Estacion.h"
#include "TablaHash.h"

using namespace std;

class Sistema
{
private:
    TablaHash<string, Estacion> estaciones;
    bool cargado;

public:
    // Crea el sistema sin datos cargados.
    Sistema()
    {
        cargado = false;
    }

    // Carga las estaciones desde la carpeta indicada.
    bool cargarDatos(string carpeta);

    // Muestra un resumen del sistema.
    void resumen() const;

    // Busca una estación por código.
    Estacion* buscarEstacion(string codigo);

    // Agrega una estación si sus datos son válidos y el código no existe.
    bool agregarEstacion(string codigo, string nombre, string barrio,
                         int capacidad, int disponibles);

    // Elimina una estación por código.
    bool eliminarEstacion(string codigo);
};

#endif
