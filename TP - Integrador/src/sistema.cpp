#include <fstream>
#include <iostream>
#include "Sistema.h"

using namespace std;

// Carga los archivos de datos y agrega las estaciones a la tabla hash.
bool Sistema::cargarDatos(string carpeta)
{
    cout << "Cargando datos desde archivos..." << endl;
    if (cargado)
    {
        cout << "Los datos ya fueron cargados. Reinicie para restaurarlos." << endl;
        return false;
    }

    ifstream levantarEstaciones(carpeta + "/estaciones.txt");
    ifstream levantarBicicletas(carpeta + "/bicicletas.txt");
    ifstream levantarViajes(carpeta + "/viajes.txt");
    ifstream levantarCiclovias(carpeta + "/ciclovias.txt");

    if (!levantarEstaciones || !levantarBicicletas || !levantarViajes || !levantarCiclovias)
    {
        cout << "No se pudieron abrir los archivos de datos." << endl;
        return false;
    }

    string codigo;
    string nombre;
    string barrio;
    int capacidad;
    int disponibles;

    bool lecturaCorrecta = true;
    while (lecturaCorrecta)
    {
        levantarEstaciones >> codigo;
        if (levantarEstaciones.fail())
        {
            lecturaCorrecta = false;
        }
        else
        {
            levantarEstaciones >> nombre;
            levantarEstaciones >> barrio;
            levantarEstaciones >> capacidad;
            levantarEstaciones >> disponibles;

            if (levantarEstaciones.fail())
            {
                cout << "Registro de estacion incompleto o invalido." << endl;
                return false;
            }

            if (!agregarEstacion(codigo, nombre, barrio, capacidad, disponibles))
            {
                cout << "Estacion invalida o repetida: " << codigo << endl;
                return false;
            }
        }
    }

    cargado = true;
    cout << "Datos cargados correctamente." << endl;
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

// Ordena las estaciones de menor a mayor según el criterio elegido.
void Sistema::listarEstacionesOrdenadas(int criterio)
{
    if (criterio != 1 && criterio != 2)
    {
        cout << "Opcion invalida." << endl;
        return;
    }

    size_t cantidadEstaciones = estaciones.tamano();
    if (cantidadEstaciones == 0)
    {
        cout << "No hay estaciones cargadas." << endl;
        return;
    }

    Estacion** ordenadas = new Estacion*[cantidadEstaciones];
    estaciones.copiarReferencias(ordenadas);

    size_t i;
    size_t j;
    size_t posicionMenor;
    int valorActual;
    int valorMenor;
    // Selección: busca el menor de las estaciones que todavía no están ordenadas.
    for (i = 0; i < cantidadEstaciones; ++i)
    {
        posicionMenor = i;
        // Compara las estaciones siguientes con la menor encontrada.
        for (j = i + 1; j < cantidadEstaciones; ++j)
        {
            if (criterio == 1)
            {
                valorActual = ordenadas[j]->getCapacidadAnclajes();
                valorMenor = ordenadas[posicionMenor]->getCapacidadAnclajes();
            }
            else
            {
                valorActual = ordenadas[j]->getBicisDisponibles();
                valorMenor = ordenadas[posicionMenor]->getBicisDisponibles();
            }

            if (valorActual < valorMenor)
                posicionMenor = j;
        }

        // Coloca el menor valor encontrado en la posición actual.
        if (posicionMenor != i)
        {
            Estacion* auxiliar = ordenadas[i];
            ordenadas[i] = ordenadas[posicionMenor];
            ordenadas[posicionMenor] = auxiliar;
        }
    }

    if (criterio == 1)
        cout << "Estaciones ordenadas por capacidad de anclajes:" << endl;
    else
        cout << "Estaciones ordenadas por bicicletas disponibles:" << endl;

    for (i = 0; i < cantidadEstaciones; ++i)
    {
        ordenadas[i]->mostrarEstacion();
        cout << "------------------------------" << endl;
    }

    delete[] ordenadas;
}
