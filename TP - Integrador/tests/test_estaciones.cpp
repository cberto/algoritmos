#include <cassert>
#include <sstream>
#include <string>
#include "Sistema.h"

using namespace std;

// Comprueba la carga y consulta de una estación existente.
static void probarBusquedaYPresentacion()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    Estacion* estacion = sistema.buscarEstacion("PLZ");
    assert(estacion != nullptr);

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    estacion->mostrarEstacion();
    cout.rdbuf(salidaAnterior);
    string texto = datos.str();
    assert(texto.find("PlazaDeMayo") != string::npos);
    assert(texto.find("Monserrat") != string::npos);
}

// Comprueba el alta, las validaciones y la baja de una estación.
static void probarAltaYBaja()
{
    Sistema sistema;

    assert(sistema.agregarEstacion("NEW", "Nueva", "Barrio", 10, 3));
    Estacion* estacion = sistema.buscarEstacion("NEW");
    assert(estacion != nullptr);
    assert(estacion->getCodigo() == "NEW");

    assert(!sistema.agregarEstacion("NEW", "Otra", "Barrio", 10, 3));
    assert(!sistema.agregarEstacion("BAD", "Bad", "Barrio", 0, 0));
    assert(!sistema.agregarEstacion("BAD", "Bad", "Barrio", 10, -1));
    assert(!sistema.agregarEstacion("BAD", "Bad", "Barrio", 10, 11));

    assert(sistema.eliminarEstacion("NEW"));
    assert(sistema.buscarEstacion("NEW") == nullptr);
    assert(!sistema.eliminarEstacion("NEW"));
}

// Comprueba el orden por capacidad y por bicicletas disponibles.
static void probarOrdenamiento()
{
    Sistema sistema;
    assert(sistema.agregarEstacion("A", "A", "Barrio", 30, 5));
    assert(sistema.agregarEstacion("B", "B", "Barrio", 10, 9));
    assert(sistema.agregarEstacion("C", "C", "Barrio", 20, 7));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarEstacionesOrdenadas(1);
    cout.rdbuf(salidaAnterior);
    string texto = datos.str();
    size_t posicionA = texto.find("Codigo: A");
    size_t posicionB = texto.find("Codigo: B");
    size_t posicionC = texto.find("Codigo: C");
    assert(posicionA != string::npos && posicionB != string::npos
           && posicionC != string::npos);
    assert(posicionB < posicionC && posicionC < posicionA);

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarEstacionesOrdenadas(2);
    cout.rdbuf(salidaAnterior);
    texto = datos.str();
    posicionA = texto.find("Codigo: A");
    posicionB = texto.find("Codigo: B");
    posicionC = texto.find("Codigo: C");
    assert(posicionA != string::npos && posicionB != string::npos
           && posicionC != string::npos);
    assert(posicionA < posicionC && posicionC < posicionB);
}

// Comprueba el filtro de ocupación y el límite estricto del 20%.
static void probarOcupacionBaja()
{
    Sistema sistema;
    assert(sistema.agregarEstacion("A", "A", "Barrio", 20, 3));
    assert(sistema.agregarEstacion("B", "B", "Barrio", 10, 2));
    assert(sistema.agregarEstacion("C", "C", "Barrio", 50, 15));
    assert(sistema.agregarEstacion("D", "D", "Barrio", 40, 7));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarEstacionesBajaOcupacion();
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    assert(texto.find("Codigo: A") != string::npos);
    assert(texto.find("Codigo: D") != string::npos);
    assert(texto.find("Codigo: B") == string::npos);
    assert(texto.find("Codigo: C") == string::npos);
}

// Captura el resultado que muestra el cálculo de camino mínimo.
static string obtenerSalidaCamino(Sistema& sistema, string origen, string destino)
{
    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.mostrarCaminoMinimo(origen, destino);
    cout.rdbuf(salidaAnterior);
    return datos.str();
}

// Comprueba el camino BFS y el caso de estaciones sin conexión.
static void probarCaminoMinimo()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    string texto = obtenerSalidaCamino(sistema, "PAL", "RET");
    assert(texto.find("(3 tramos)") != string::npos);
    assert(texto.find("PAL -> CAB -> PLZ -> RET") != string::npos);

    assert(sistema.agregarEstacion("AIS", "Aislada", "Barrio", 10, 0));
    texto = obtenerSalidaCamino(sistema, "PLZ", "AIS");
    assert(texto.find("No existe un recorrido") != string::npos);
}

// Comprueba el conteo por origen y rango inclusivo de fechas.
static void probarCantidadViajesSalidos()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    assert(sistema.contarViajesSalidos("PLZ", 20260310, 20260315) == 2);
    assert(sistema.contarViajesSalidos("PLZ", 20260311, 20260314) == 0);
    assert(sistema.contarViajesSalidos("PAL", 20260311, 20260311) == 1);
}

// Ejecuta las pruebas del módulo de estaciones.
int main()
{
    probarBusquedaYPresentacion();
    probarAltaYBaja();
    probarOrdenamiento();
    probarOcupacionBaja();
    probarCaminoMinimo();
    probarCantidadViajesSalidos();
}
