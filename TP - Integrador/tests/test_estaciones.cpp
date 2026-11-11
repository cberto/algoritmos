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

// Ejecuta las pruebas del módulo de estaciones.
int main()
{
    probarBusquedaYPresentacion();
    probarAltaYBaja();
}
