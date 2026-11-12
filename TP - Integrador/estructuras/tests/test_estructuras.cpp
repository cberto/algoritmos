#include <cassert>
#include <string>
#include "ArbolBinarioBusqueda.h"
#include "Cola.h"
#include "Grafo.h"
#include "ListaEnlazada.h"
#include "MonticuloMinimo.h"
#include "TablaHash.h"

using namespace std;

static int recorrido[8];
static int recorridoActual;

// Guarda cada clave del recorrido.
static void guardarPar(int clave, int)
{
    recorrido[recorridoActual++] = clave;
}

// Indica si el valor es par.
static bool esPar(int, int valor)
{
    return valor % 2 == 0;
}

struct Trabajo
{
    int prioridad;
    int id;

    // Crea un trabajo vacío para recibir datos extraídos del heap.
    Trabajo()
    {
        prioridad = 0;
        id = 0;
    }

    // Crea un trabajo con prioridad e identificador.
    Trabajo(int prioridadNueva, int idNuevo)
    {
        prioridad = prioridadNueva;
        id = idNuevo;
    }

    // Compara los trabajos por prioridad.
    bool operator<(Trabajo otro) const
    {
        return prioridad < otro.prioridad;
    }
};

// Comprueba inserción, consulta y borrado en la lista.
static void probarLista()
{
    ListaEnlazada<int> lista;
    int dato = 0;
    assert(lista.vacia());
    assert(!lista.eliminarPrimero(dato));

    lista.insertarAlFinal(2);
    lista.insertarAlInicio(1);
    lista.insertarAlFinal(3);
    assert(lista.tamano() == 3);
    assert(lista.obtener(1, dato) && dato == 2);
    int elementos[3];
    lista.copiarElementos(elementos);
    assert(elementos[0] == 1 && elementos[1] == 2 && elementos[2] == 3);
    assert(lista.eliminar(2));
    assert(!lista.eliminar(9));
    assert(lista.eliminarPrimero(dato) && dato == 1);
    assert(lista.eliminarPrimero(dato) && dato == 3);
    assert(lista.vacia());

}

// Comprueba el comportamiento FIFO de la cola.
static void probarCola()
{
    Cola<string> cola;
    string dato;
    assert(!cola.consultarFrente(dato));
    assert(!cola.desencolar(dato));

    cola.encolar("primero");
    cola.encolar("segundo");
    assert(cola.consultarFrente(dato) && dato == "primero");
    assert(cola.desencolar(dato) && dato == "primero");
    assert(cola.desencolar(dato) && dato == "segundo");
    assert(cola.vacia());

}

// Comprueba colisiones, búsqueda y borrado en la tabla.
static void probarTablaHash()
{
    TablaHash<string, int> tabla(1);
    assert(tabla.insertar("PLZ", 12));
    assert(tabla.insertar("CAB", 4));
    assert(!tabla.insertar("PLZ", 99));
    assert(*tabla.buscar("CAB") == 4);
    assert(tabla.cantidadColisiones() == 1);
    assert(tabla.factorCarga() == 2.0);
    assert(tabla.eliminar("PLZ"));
    assert(tabla.buscar("PLZ") == nullptr);
    assert(!tabla.eliminar("ausente"));

    TablaHash<int, string> tablaEnteros;
    assert(tablaEnteros.insertar(42, "valor"));
    assert(*tablaEnteros.buscar(42) == "valor");
    string* referencia[1];
    tablaEnteros.copiarReferencias(referencia);
    assert(*referencia[0] == "valor");

}

// Comprueba recorridos, métricas y eliminaciones del ABB.
static void probarArbol()
{
    ArbolBinarioBusqueda<int, int> arbol;
    assert(arbol.altura() == -1);
    assert(arbol.insertar(5, 50));
    assert(arbol.insertar(3, 31));
    assert(arbol.insertar(7, 70));
    assert(arbol.insertar(2, 21));
    assert(arbol.insertar(4, 40));
    assert(!arbol.insertar(5, 500));
    assert(*arbol.buscar(4) == 40);
    assert(arbol.altura() == 2);
    assert(arbol.contarNodos() == 5);
    assert(arbol.contarSi(esPar) == 3);

    recorridoActual = 0;
    arbol.recorrerInorden(guardarPar);
    assert(recorridoActual == 5);
    assert(recorrido[0] == 2 && recorrido[4] == 7);

    assert(arbol.eliminar(2));
    assert(arbol.eliminar(3));
    assert(arbol.eliminar(5));
    assert(!arbol.eliminar(99));
    assert(arbol.tamano() == 2);
    assert(arbol.contarNodos() == 2);

}

// Comprueba prioridades y expansión del arreglo del heap.
static void probarMonticulo()
{
    MonticuloMinimo<Trabajo> monticulo;
    Trabajo trabajo;
    assert(!monticulo.extraerMinimo(trabajo));

    monticulo.insertar(Trabajo(3, 30));
    monticulo.insertar(Trabajo(1, 10));
    monticulo.insertar(Trabajo(2, 20));
    assert(monticulo.consultarMinimo(trabajo) && trabajo.id == 10);
    assert(monticulo.extraerMinimo(trabajo) && trabajo.id == 10);
    assert(monticulo.extraerMinimo(trabajo) && trabajo.id == 20);
    assert(monticulo.extraerMinimo(trabajo) && trabajo.id == 30);
    assert(monticulo.vacio());

    int i;
    for (i = 0; i < 20; ++i)
    {
        int prioridad = 20 - i;
        monticulo.insertar(Trabajo(prioridad, prioridad));
    }
    for (i = 0; i < 20; ++i)
    {
        int prioridad = i + 1;
        assert(monticulo.extraerMinimo(trabajo) && trabajo.prioridad == prioridad);
    }

}

// Comprueba conexiones y caminos mínimos del grafo.
static void probarGrafo()
{
    Grafo<string> grafo;
    ListaEnlazada<string> camino;
    string estacion;

    assert(grafo.agregarVertice("PLZ"));
    assert(grafo.agregarVertice("CAB"));
    assert(grafo.agregarVertice("PAL"));
    assert(grafo.agregarVertice("RET"));
    assert(!grafo.agregarVertice("PLZ"));
    assert(grafo.conectar("PLZ", "CAB"));
    assert(grafo.conectar("CAB", "PAL"));
    assert(!grafo.conectar("PLZ", "CAB"));
    assert(!grafo.conectar("PLZ", "NOPE"));
    assert(grafo.caminoMinimo("PLZ", "PAL", camino));
    assert(camino.tamano() == 3);
    assert(camino.obtener(0, estacion) && estacion == "PLZ");
    assert(camino.obtener(1, estacion) && estacion == "CAB");
    assert(camino.obtener(2, estacion) && estacion == "PAL");
    assert(grafo.caminoMinimo("PAL", "PLZ", camino));
    assert(camino.obtener(0, estacion) && estacion == "PAL");
    assert(camino.obtener(2, estacion) && estacion == "PLZ");
    assert(grafo.caminoMinimo("PLZ", "PLZ", camino));
    assert(camino.tamano() == 1);
    assert(!grafo.caminoMinimo("PLZ", "RET", camino));
    assert(camino.vacia());
    assert(grafo.eliminarVertice("CAB"));
    assert(!grafo.contiene("CAB"));
    assert(!grafo.caminoMinimo("PLZ", "PAL", camino));
    assert(grafo.cantidadVertices() == 3);

}

// Ejecuta las pruebas de cada estructura.
int main()
{
    probarLista();
    probarCola();
    probarTablaHash();
    probarArbol();
    probarMonticulo();
    probarGrafo();
}
