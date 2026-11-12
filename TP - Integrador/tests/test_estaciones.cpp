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

// Comprueba la lista de viajes por DNI y la suma de sus duraciones.
static void probarViajesPorDni()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.mostrarViajesPorDni(30123456);
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    assert(texto.find("Viaje: 9001") != string::npos);
    assert(texto.find("Viaje: 9003") != string::npos);
    assert(texto.find("Total de minutos pedaleados: 43") != string::npos);

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.mostrarViajesPorDni(11111111);
    cout.rdbuf(salidaAnterior);
    texto = datos.str();
    assert(texto.find("No se encontraron viajes") != string::npos);
    assert(texto.find("Total de minutos pedaleados: 0") != string::npos);
}

// Comprueba el filtro estricto de kilometraje y los casos sin resultados.
static void probarBicicletasPorKilometraje()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasMasKilometros(1500);
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    assert(texto.find("Bicicleta: 502") != string::npos);
    assert(texto.find("Bicicleta: 504") != string::npos);
    assert(texto.find("Bicicleta: 505") != string::npos);
    assert(texto.find("Bicicleta: 507") == string::npos);

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasMasKilometros(5000);
    cout.rdbuf(salidaAnterior);
    texto = datos.str();
    assert(texto.find("No hay bicicletas con mas de 5000 kilometros") != string::npos);

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasMasKilometros(-1);
    cout.rdbuf(salidaAnterior);
    texto = datos.str();
    assert(texto.find("debe ser cero o mayor") != string::npos);
}

// Comprueba la espera FIFO independiente para cada estación.
static void probarColaDeEspera()
{
    Sistema sistema;
    assert(sistema.agregarEstacion("Q1", "EstacionUno", "Barrio", 2, 1));
    assert(sistema.agregarEstacion("Q2", "EstacionDos", "Barrio", 2, 0));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.solicitarBicicleta("Q1", 100);
    sistema.solicitarBicicleta("Q1", 101);
    sistema.solicitarBicicleta("Q1", 102);
    sistema.solicitarBicicleta("Q2", 201);

    assert(sistema.buscarEstacion("Q1")->getBicisDisponibles() == 0);
    sistema.devolverBicicleta("Q1");
    assert(sistema.buscarEstacion("Q1")->getBicisDisponibles() == 0);
    sistema.devolverBicicleta("Q1");
    assert(sistema.buscarEstacion("Q1")->getBicisDisponibles() == 0);
    sistema.devolverBicicleta("Q1");
    assert(sistema.buscarEstacion("Q1")->getBicisDisponibles() == 1);
    sistema.devolverBicicleta("Q1");
    assert(sistema.buscarEstacion("Q1")->getBicisDisponibles() == 2);
    sistema.devolverBicicleta("Q1");
    sistema.devolverBicicleta("Q2");
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    size_t usuario101 = texto.find("asignada al primer usuario en espera: 101");
    size_t usuario102 = texto.find("asignada al primer usuario en espera: 102");
    size_t usuario201 = texto.find("asignada al primer usuario en espera: 201");
    assert(usuario101 != string::npos);
    assert(usuario102 != string::npos);
    assert(usuario201 != string::npos);
    assert(usuario101 < usuario102);
    assert(texto.find("La estacion ya esta completa.") != string::npos);
}

// Comprueba el ingreso por prioridad y la extracción del más urgente.
static void probarTaller()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.ingresarBicicletaAlTaller(501);
    sistema.ingresarBicicletaAlTaller(505);
    sistema.ingresarBicicletaAlTaller(502);
    sistema.ingresarBicicletaAlTaller(999);
    sistema.extraerBicicletaDelTaller();
    sistema.extraerBicicletaDelTaller();
    sistema.extraerBicicletaDelTaller();
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    size_t bicicletaElectrica = texto.find("Bicicleta: 502");
    size_t bicicletaMecanica = texto.find("Bicicleta: 505");
    size_t prioridadElectrica = texto.find("Prioridad: 1");
    size_t prioridadMecanica = texto.find("Prioridad: 2");
    assert(texto.find("Solo se pueden ingresar bicicletas averiadas") != string::npos);
    assert(texto.find("Bicicleta no encontrada") != string::npos);
    assert(bicicletaElectrica != string::npos);
    assert(bicicletaMecanica != string::npos);
    assert(bicicletaElectrica < bicicletaMecanica);
    assert(prioridadElectrica != string::npos);
    assert(prioridadMecanica != string::npos);
    assert(prioridadElectrica < bicicletaElectrica);
    assert(prioridadMecanica < bicicletaMecanica);
    assert(texto.find("No hay bicicletas en el taller.") != string::npos);
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
    probarViajesPorDni();
    probarBicicletasPorKilometraje();
    probarColaDeEspera();
    probarTaller();
}
