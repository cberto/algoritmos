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

// Comprueba que la carga inserta las bicicletas y que el ABB rechaza IDs repetidos.
static void probarInsercionBicicletasEnABB()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    Bicicleta existente(501, "PLZ", "Mecanica", "OK", 1240);
    Bicicleta nueva(508, "BOE", "Mecanica", "OK", 100);
    assert(!sistema.insertarBicicletaEnABB(existente));
    assert(sistema.insertarBicicletaEnABB(nueva));
    assert(!sistema.insertarBicicletaEnABB(nueva));
}

// Comprueba la búsqueda por ID, la presentación y el ID inexistente.
static void probarBusquedaBicicletaPorId()
{
    Sistema sistema;
    assert(sistema.cargarDatos("data"));

    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.mostrarBicicletaPorId(502);
    sistema.mostrarBicicletaPorId(999);
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    assert(texto.find("Bicicleta encontrada:") != string::npos);
    assert(texto.find("Bicicleta: 502") != string::npos);
    assert(texto.find("Estacion: PAL") != string::npos);
    assert(texto.find("Tipo: Electrica") != string::npos);
    assert(texto.find("Estado: Averiada") != string::npos);
    assert(texto.find("Kilometros: 3810") != string::npos);
    assert(texto.find("Bicicleta no encontrada.") != string::npos);
}

// Comprueba que inorder presenta IDs ascendentes y resuelve el árbol vacío.
static void probarListadoBicicletasInorden()
{
    Sistema sistema;
    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasInorden();
    cout.rdbuf(salidaAnterior);
    assert(datos.str().find("No hay bicicletas en el ABB.") != string::npos);

    Bicicleta bicicleta30(30, "B", "Mecanica", "OK", 300);
    Bicicleta bicicleta10(10, "A", "Electrica", "OK", 100);
    Bicicleta bicicleta20(20, "C", "Mecanica", "Averiada", 200);
    assert(sistema.insertarBicicletaEnABB(bicicleta30));
    assert(sistema.insertarBicicletaEnABB(bicicleta10));
    assert(sistema.insertarBicicletaEnABB(bicicleta20));

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasInorden();
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    size_t posicion10 = texto.find("Bicicleta: 10");
    size_t posicion20 = texto.find("Bicicleta: 20");
    size_t posicion30 = texto.find("Bicicleta: 30");
    assert(posicion10 != string::npos);
    assert(posicion20 != string::npos);
    assert(posicion30 != string::npos);
    assert(posicion10 < posicion20 && posicion20 < posicion30);
}

// Comprueba el conteo por estado y el resultado para el ABB vacío.
static void probarConteoBicicletasAveriadas()
{
    Sistema vacio;
    assert(vacio.contarBicicletasAveriadas() == 0);

    Sistema sistema;
    assert(sistema.cargarDatos("data"));
    assert(sistema.contarBicicletasAveriadas() == 2);

    Bicicleta averiada(508, "BOE", "Mecanica", "Averiada", 700);
    Bicicleta enBuenEstado(509, "BOE", "Mecanica", "OK", 800);
    assert(sistema.insertarBicicletaEnABB(averiada));
    assert(sistema.insertarBicicletaEnABB(enBuenEstado));
    assert(sistema.contarBicicletasAveriadas() == 3);
}

// Comprueba la altura vacía, balanceada y degenerada del ABB.
static void probarAlturaBicicletasABB()
{
    Sistema vacio;
    assert(vacio.alturaBicicletasABB() == -1);

    Sistema balanceado;
    Bicicleta bicicleta20(20, "A", "Mecanica", "OK", 200);
    Bicicleta bicicleta10(10, "A", "Mecanica", "OK", 100);
    Bicicleta bicicleta30(30, "A", "Mecanica", "OK", 300);
    Bicicleta bicicleta5(5, "A", "Mecanica", "OK", 50);
    assert(balanceado.insertarBicicletaEnABB(bicicleta20));
    assert(balanceado.insertarBicicletaEnABB(bicicleta10));
    assert(balanceado.insertarBicicletaEnABB(bicicleta30));
    assert(balanceado.alturaBicicletasABB() == 1);
    assert(balanceado.insertarBicicletaEnABB(bicicleta5));
    assert(balanceado.alturaBicicletasABB() == 2);

    Sistema degenerado;
    Bicicleta bicicleta1(1, "A", "Mecanica", "OK", 10);
    Bicicleta bicicleta2(2, "A", "Mecanica", "OK", 20);
    Bicicleta bicicleta3(3, "A", "Mecanica", "OK", 30);
    assert(degenerado.insertarBicicletaEnABB(bicicleta1));
    assert(degenerado.insertarBicicletaEnABB(bicicleta2));
    assert(degenerado.insertarBicicletaEnABB(bicicleta3));
    assert(degenerado.alturaBicicletasABB() == 2);
}

// Captura el listado inorder para comprobar que el ABB conserva su orden.
static string obtenerListadoBicicletas(Sistema& sistema)
{
    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.listarBicicletasInorden();
    cout.rdbuf(salidaAnterior);
    return datos.str();
}

// Comprueba la eliminación de hojas, nodos con un hijo y nodos con dos hijos.
static void probarEliminacionBicicletasDelABB()
{
    Sistema hoja;
    Bicicleta bicicleta20(20, "A", "Mecanica", "OK", 200);
    Bicicleta bicicleta10(10, "A", "Mecanica", "OK", 100);
    Bicicleta bicicleta30(30, "A", "Mecanica", "OK", 300);
    assert(hoja.insertarBicicletaEnABB(bicicleta20));
    assert(hoja.insertarBicicletaEnABB(bicicleta10));
    assert(hoja.insertarBicicletaEnABB(bicicleta30));
    assert(hoja.eliminarBicicletaDelABB(10));
    assert(!hoja.eliminarBicicletaDelABB(10));
    string texto = obtenerListadoBicicletas(hoja);
    size_t posicion20 = texto.find("Bicicleta: 20");
    size_t posicion30 = texto.find("Bicicleta: 30");
    assert(posicion20 != string::npos && posicion30 != string::npos);
    assert(posicion20 < posicion30);
    assert(texto.find("Bicicleta: 10") == string::npos);

    Sistema unHijo;
    Bicicleta bicicleta40(40, "A", "Mecanica", "OK", 400);
    Bicicleta bicicleta35(35, "A", "Mecanica", "OK", 350);
    Bicicleta bicicleta50(50, "A", "Mecanica", "OK", 500);
    assert(unHijo.insertarBicicletaEnABB(bicicleta40));
    assert(unHijo.insertarBicicletaEnABB(bicicleta35));
    assert(unHijo.insertarBicicletaEnABB(bicicleta50));
    Bicicleta bicicleta30UnHijo(30, "A", "Mecanica", "OK", 300);
    assert(unHijo.insertarBicicletaEnABB(bicicleta30UnHijo));
    assert(unHijo.eliminarBicicletaDelABB(35));
    assert(!unHijo.eliminarBicicletaDelABB(35));
    texto = obtenerListadoBicicletas(unHijo);
    size_t posicion30UnHijo = texto.find("Bicicleta: 30");
    size_t posicion40UnHijo = texto.find("Bicicleta: 40");
    size_t posicion50UnHijo = texto.find("Bicicleta: 50");
    assert(posicion30UnHijo != string::npos && posicion40UnHijo != string::npos
           && posicion50UnHijo != string::npos);
    assert(posicion30UnHijo < posicion40UnHijo
           && posicion40UnHijo < posicion50UnHijo);
    assert(texto.find("Bicicleta: 35") == string::npos);

    Sistema dosHijos;
    Bicicleta bicicleta60(60, "A", "Mecanica", "OK", 600);
    Bicicleta bicicleta55(55, "A", "Mecanica", "OK", 550);
    Bicicleta bicicleta70(70, "A", "Mecanica", "OK", 700);
    Bicicleta bicicleta65(65, "A", "Mecanica", "OK", 650);
    Bicicleta bicicleta75(75, "A", "Mecanica", "OK", 750);
    assert(dosHijos.insertarBicicletaEnABB(bicicleta60));
    assert(dosHijos.insertarBicicletaEnABB(bicicleta55));
    assert(dosHijos.insertarBicicletaEnABB(bicicleta70));
    assert(dosHijos.insertarBicicletaEnABB(bicicleta65));
    assert(dosHijos.insertarBicicletaEnABB(bicicleta75));
    assert(dosHijos.eliminarBicicletaDelABB(60));
    texto = obtenerListadoBicicletas(dosHijos);
    size_t posicion55 = texto.find("Bicicleta: 55");
    size_t posicion65 = texto.find("Bicicleta: 65");
    size_t posicion70 = texto.find("Bicicleta: 70");
    size_t posicion75 = texto.find("Bicicleta: 75");
    assert(posicion55 != string::npos && posicion65 != string::npos
           && posicion70 != string::npos && posicion75 != string::npos);
    assert(posicion55 < posicion65 && posicion65 < posicion70
           && posicion70 < posicion75);
    assert(texto.find("Bicicleta: 60") == string::npos);
}

// Comprueba si un código aparece como elemento completo de una combinación.
static bool codigoEnCombinacion(string combinacion, string codigo)
{
    size_t posicion = combinacion.find(codigo);
    if (posicion == string::npos)
        return false;

    bool inicioValido = posicion == 0;
    if (!inicioValido && posicion >= 2)
        inicioValido = combinacion.substr(posicion - 2, 2) == ", ";

    size_t finCodigo = posicion + codigo.length();
    bool finValido = finCodigo == combinacion.length();
    if (!finValido && finCodigo + 2 <= combinacion.length())
        finValido = combinacion.substr(finCodigo, 2) == ", ";

    return inicioValido && finValido;
}

// Busca una combinación sin depender del orden interno de la tabla hash.
static bool contieneCombinacion(string salida, string codigoA, string codigoB,
                                string codigoC)
{
    size_t inicio = 0;
    while (inicio < salida.length())
    {
        size_t apertura = salida.find('{', inicio);
        if (apertura == string::npos)
            return false;

        size_t cierre = salida.find('}', apertura);
        if (cierre == string::npos)
            return false;

        string combinacion = salida.substr(apertura + 1, cierre - apertura - 1);
        int cantidadCodigos = 1;
        size_t i;
        for (i = 0; i < combinacion.length(); ++i)
        {
            if (combinacion[i] == ',')
                ++cantidadCodigos;
        }

        int cantidadEsperada = codigoC.empty() ? 2 : 3;
        bool contieneCodigos = codigoEnCombinacion(combinacion, codigoA)
                            && codigoEnCombinacion(combinacion, codigoB);
        if (!codigoC.empty())
            contieneCodigos = contieneCodigos
                           && codigoEnCombinacion(combinacion, codigoC);

        if (cantidadCodigos == cantidadEsperada && contieneCodigos)
            return true;

        inicio = cierre + 1;
    }
    return false;
}

// Comprueba las soluciones de ejemplo y los casos sin solución e inválido.
static void probarRedistribucionBacktracking()
{
    Sistema sinEstaciones;
    ostringstream datos;
    streambuf* salidaAnterior = cout.rdbuf(datos.rdbuf());
    sinEstaciones.buscarRedistribuciones(10);
    cout.rdbuf(salidaAnterior);
    assert(datos.str().find("No hay estaciones cargadas.") != string::npos);

    Sistema sistema;
    assert(sistema.agregarEstacion("PLZ", "Plaza", "Barrio", 3, 0));
    assert(sistema.agregarEstacion("CAB", "Cabildo", "Barrio", 7, 0));
    assert(sistema.agregarEstacion("RET", "Retiro", "Barrio", 5, 0));
    assert(sistema.agregarEstacion("CON", "Congreso", "Barrio", 2, 0));
    assert(sistema.agregarEstacion("BOE", "Boedo", "Barrio", 5, 0));

    datos.str("");
    salidaAnterior = cout.rdbuf(datos.rdbuf());
    sistema.buscarRedistribuciones(10);
    sistema.buscarRedistribuciones(1);
    sistema.buscarRedistribuciones(0);
    cout.rdbuf(salidaAnterior);

    string texto = datos.str();
    assert(contieneCombinacion(texto, "PLZ", "CAB", ""));
    assert(contieneCombinacion(texto, "RET", "BOE", ""));
    assert(contieneCombinacion(texto, "PLZ", "RET", "CON"));
    assert(contieneCombinacion(texto, "PLZ", "CON", "BOE"));

    size_t cantidadSoluciones = 0;
    size_t posicion = texto.find('{');
    while (posicion != string::npos)
    {
        ++cantidadSoluciones;
        posicion = texto.find('{', posicion + 1);
    }
    assert(cantidadSoluciones == 4);
    assert(texto.find("No hay combinaciones de estaciones") != string::npos);
    assert(texto.find("La capacidad del camion debe ser positiva.") != string::npos);
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
    probarInsercionBicicletasEnABB();
    probarBusquedaBicicletaPorId();
    probarListadoBicicletasInorden();
    probarConteoBicicletasAveriadas();
    probarAlturaBicicletasABB();
    probarEliminacionBicicletasDelABB();
    probarRedistribucionBacktracking();
    probarColaDeEspera();
    probarTaller();
}
