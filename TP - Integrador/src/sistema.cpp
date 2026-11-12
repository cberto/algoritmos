#include <fstream>
#include <iostream>
#include "Sistema.h"

using namespace std;

// Coordina la carga de los archivos de datos.
bool Sistema::cargarDatos(string carpeta)
{
    cout << "Cargando datos desde archivos..." << endl;
    if (cargado)
    {
        cout << "Los datos ya fueron cargados. Reinicie para restaurarlos." << endl;
        return false;
    }

    ifstream levantarBicicletas(carpeta + "/bicicletas.txt");
    if (!levantarBicicletas)
    {
        cout << "No se pudieron abrir los archivos de datos." << endl;
        return false;
    }

    if (!cargarEstaciones(carpeta))
        return false;
    if (!cargarViajes(carpeta))
        return false;
    if (!cargarCiclovias(carpeta))
        return false;

    cargado = true;
    cout << "Datos cargados correctamente." << endl;
    return true;
}

// Carga los registros de estaciones en la tabla hash y el grafo.
bool Sistema::cargarEstaciones(string carpeta)
{
    ifstream levantarEstaciones(carpeta + "/estaciones.txt");
    if (!levantarEstaciones)
    {
        cout << "No se pudo abrir estaciones.txt." << endl;
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
    return true;
}

// Carga los viajes en la lista enlazada.
bool Sistema::cargarViajes(string carpeta)
{
    ifstream levantarViajes(carpeta + "/viajes.txt");
    if (!levantarViajes)
    {
        cout << "No se pudo abrir viajes.txt." << endl;
        return false;
    }

    int viajeId;
    int biciId;
    int dniUsuario;
    string origenViaje;
    string destinoViaje;
    int fechaViaje;
    int duracionMinutos;
    bool leyendoViajes = true;
    while (leyendoViajes)
    {
        levantarViajes >> viajeId;
        if (levantarViajes.fail())
        {
            leyendoViajes = false;
        }
        else
        {
            levantarViajes >> biciId;
            levantarViajes >> dniUsuario;
            levantarViajes >> origenViaje;
            levantarViajes >> destinoViaje;
            levantarViajes >> fechaViaje;
            levantarViajes >> duracionMinutos;

            if (levantarViajes.fail())
            {
                cout << "Registro de viaje incompleto o invalido." << endl;
                return false;
            }

            Viaje nuevoViaje(viajeId, biciId, dniUsuario, origenViaje,
                             destinoViaje, fechaViaje, duracionMinutos);
            viajes.insertarAlFinal(nuevoViaje);
        }
    }
    return true;
}

// Carga las conexiones bidireccionales de ciclovías en el grafo.
bool Sistema::cargarCiclovias(string carpeta)
{
    ifstream levantarCiclovias(carpeta + "/ciclovias.txt");
    if (!levantarCiclovias)
    {
        cout << "No se pudo abrir ciclovias.txt." << endl;
        return false;
    }

    string estacionA;
    string estacionB;
    bool leyendoCiclovias = true;
    while (leyendoCiclovias)
    {
        levantarCiclovias >> estacionA;
        if (levantarCiclovias.fail())
        {
            leyendoCiclovias = false;
        }
        else
        {
            levantarCiclovias >> estacionB;
            if (levantarCiclovias.fail())
            {
                cout << "Registro de ciclovia incompleto." << endl;
                return false;
            }

            if (!ciclovias.conectar(estacionA, estacionB))
            {
                cout << "No se pudo conectar " << estacionA << " con " << estacionB << "." << endl;
                return false;
            }
        }
    }
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
    if (!estaciones.insertar(codigo, nueva))
        return false;

    if (!ciclovias.agregarVertice(codigo))
    {
        estaciones.eliminar(codigo);
        return false;
    }
    return true;
}

// Elimina la estación y su valor de la tabla hash.
bool Sistema::eliminarEstacion(string codigo)
{
    if (estaciones.buscar(codigo) == nullptr)
        return false;

    ciclovias.eliminarVertice(codigo);
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

// Muestra las estaciones cuya disponibilidad es menor al 20% de capacidad.
void Sistema::listarEstacionesBajaOcupacion()
{
    size_t cantidadEstaciones = estaciones.tamano();
    if (cantidadEstaciones == 0)
    {
        cout << "No hay estaciones cargadas." << endl;
        return;
    }

    Estacion** referencias = new Estacion*[cantidadEstaciones];
    estaciones.copiarReferencias(referencias);

    bool hayEstacionesParaMostrar = false;
    size_t i;
    int capacidad;
    int disponibles;
    double porcentajeOcupacion;
    for (i = 0; i < cantidadEstaciones; ++i)
    {
        capacidad = referencias[i]->getCapacidadAnclajes();
        disponibles = referencias[i]->getBicisDisponibles();
        if (capacidad > 0)
        {
            porcentajeOcupacion = 100.0 * disponibles / capacidad;
            if (porcentajeOcupacion < 20.0)
            {
                if (!hayEstacionesParaMostrar)
                    cout << "Estaciones con menos del 20% de ocupacion:" << endl;
                referencias[i]->mostrarEstacion();
                cout << "------------------------------" << endl;
                hayEstacionesParaMostrar = true;
            }
        }
    }

    if (!hayEstacionesParaMostrar)
        cout << "No hay estaciones con menos del 20% de ocupacion." << endl;

    delete[] referencias;
}

// Muestra el recorrido por ciclovías con menor cantidad de tramos.
void Sistema::mostrarCaminoMinimo(string origen, string destino)
{
    if (estaciones.buscar(origen) == nullptr || estaciones.buscar(destino) == nullptr)
    {
        cout << "La estacion de origen o destino no existe." << endl;
        return;
    }

    ListaEnlazada<string> camino;
    if (!ciclovias.caminoMinimo(origen, destino, camino))
    {
        cout << "No existe un recorrido entre las estaciones indicadas." << endl;
        return;
    }

    cout << "Recorrido minimo (" << camino.tamano() - 1 << " tramos):" << endl;
    string codigo;
    size_t i;
    for (i = 0; i < camino.tamano(); ++i)
    {
        camino.obtener(i, codigo);
        cout << codigo;
        if (i + 1 < camino.tamano())
            cout << " -> ";
    }
    cout << endl;
}

// Cuenta los viajes cuya estación de origen y fecha coinciden con la consulta.
int Sistema::contarViajesSalidos(string codigoEstacion, int fechaInicio, int fechaFin)
{
    size_t cantidadViajes = viajes.tamano();
    if (cantidadViajes == 0)
        return 0;

    Viaje* viajesCargados = new Viaje[cantidadViajes];
    viajes.copiarElementos(viajesCargados);

    int cantidadEncontrada = 0;
    size_t i;
    for (i = 0; i < cantidadViajes; ++i)
    {
        if (viajesCargados[i].getEstacionOrigen() == codigoEstacion
            && viajesCargados[i].getFecha() >= fechaInicio
            && viajesCargados[i].getFecha() <= fechaFin)
        {
            ++cantidadEncontrada;
        }
    }

    delete[] viajesCargados;
    return cantidadEncontrada;
}
