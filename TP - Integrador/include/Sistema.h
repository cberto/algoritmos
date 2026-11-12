#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "Estacion.h"
#include "Grafo.h"
#include "ListaEnlazada.h"
#include "TablaHash.h"
#include "Viaje.h"

using namespace std;

class Sistema
{
private:
    TablaHash<string, Estacion> estaciones;
    Grafo<string> ciclovias;
    ListaEnlazada<Viaje> viajes;
    bool cargado;

    // Carga las estaciones desde su archivo.
    bool cargarEstaciones(string carpeta);

    // Carga los viajes desde su archivo.
    bool cargarViajes(string carpeta);

    // Carga las conexiones de ciclovía desde su archivo.
    bool cargarCiclovias(string carpeta);

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

    // Lista las estaciones ordenadas por capacidad o bicicletas disponibles.
    void listarEstacionesOrdenadas(int criterio);

    // Muestra las estaciones con menos del 20% de ocupación.
    void listarEstacionesBajaOcupacion();

    // Muestra el recorrido con menos tramos entre dos estaciones.
    void mostrarCaminoMinimo(string origen, string destino);

    // Cuenta los viajes que salieron de una estación en el rango inclusivo.
    int contarViajesSalidos(string codigoEstacion, int fechaInicio, int fechaFin);
};

#endif
