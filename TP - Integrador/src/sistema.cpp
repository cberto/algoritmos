#include <fstream>
#include "Sistema.h"

using namespace std;

// Carga los archivos de datos y agrega las estaciones a la tabla hash.
bool Sistema::cargarDatos(string carpeta, ostream& salida)
{
    salida << "Cargando datos desde archivos..." << endl;
    if (cargado)
    {
        salida << "Los datos ya fueron cargados. Reinicie para restaurarlos." << endl;
        return false;
    }

    ifstream levantarEstaciones(carpeta + "/estaciones.txt");
    ifstream levantarBicicletas(carpeta + "/bicicletas.txt");
    ifstream levantarViajes(carpeta + "/viajes.txt");
    ifstream levantarCiclovias(carpeta + "/ciclovias.txt");

    if (!levantarEstaciones || !levantarBicicletas || !levantarViajes || !levantarCiclovias)
    {
        salida << "No se pudieron abrir los archivos de datos." << endl;
        return false;
    }

    string codigo;
    string nombre;
    string barrio;
    int capacidad;
    int disponibles;

    while (levantarEstaciones >> codigo >> nombre >> barrio >> capacidad >> disponibles)
    {
        if (!agregarEstacion(codigo, nombre, barrio, capacidad, disponibles))
        {
            salida << "Estacion invalida o repetida: " << codigo << endl;
            return false;
        }
    }

    cargado = true;
    salida << "Datos cargados correctamente." << endl;
    return true;
}

// Devuelve la estación asociada al código o null si no existe.
Estacion* Sistema::buscarEstacion(string codigo)
{
    return estaciones.buscar(codigo);
}

// Valida los datos y agrega una estación con código único.
bool Sistema::agregarEstacion(string codigo, string nombre, string barrio,
                              int capacidad, int disponibles)
{
    if (codigo.empty() || nombre.empty() || barrio.empty()
        || capacidad <= 0 || disponibles < 0 || disponibles > capacidad)
        return false;

    Estacion nueva(codigo, nombre, barrio, capacidad, disponibles);
    return estaciones.insertar(codigo, nueva);
}

// Elimina la estación y su valor de la tabla hash.
bool Sistema::eliminarEstacion(string codigo)
{
    return estaciones.eliminar(codigo);
}
