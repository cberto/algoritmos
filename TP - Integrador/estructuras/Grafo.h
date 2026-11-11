#ifndef ESTRUCTURAS_GRAFO_H
#define ESTRUCTURAS_GRAFO_H

#include <cstddef>
#include "Cola.h"
#include "FuncionHash.h"
#include "ListaEnlazada.h"
#include "TablaHash.h"

using namespace std;

template <typename Vertice, typename Hash = FuncionHash<Vertice>>
class Grafo
{
private:
    struct NodoVertice;

    struct NodoArista
    {
        NodoVertice* destino;
        NodoArista* siguiente;

        // Crea una arista hacia el vértice destino.
        NodoArista(NodoVertice* vertice)
        {
            destino = vertice;
            siguiente = nullptr;
        }
    };

    struct NodoVertice
    {
        Vertice dato;
        NodoArista* aristas;
        NodoVertice* siguiente;
        bool visitado;
        NodoVertice* anterior;

        // Crea un vértice sin aristas.
        NodoVertice(Vertice valor)
        {
            dato = valor;
            aristas = nullptr;
            siguiente = nullptr;
            visitado = false;
            anterior = nullptr;
        }
    };

    NodoVertice* vertices;
    size_t cantidad;
    TablaHash<Vertice, NodoVertice*, Hash> indice;

    // Indica si el origen ya tiene una arista al destino.
    bool contieneArista(NodoVertice* origen, NodoVertice* destino)
    {
        NodoArista* arista = origen->aristas;
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (arista == nullptr)
                break;
            if (arista->destino == destino)
                return true;
            arista = arista->siguiente;
        }
        return false;
    }

    // Quita del origen la arista que apunta al destino.
    void quitarArista(NodoVertice* origen, NodoVertice* destino)
    {
        NodoArista** enlace = &origen->aristas;
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (*enlace == nullptr)
                break;
            if ((*enlace)->destino == destino)
                break;
            enlace = &(*enlace)->siguiente;
        }
        if (*enlace != nullptr)
        {
            if ((*enlace)->destino != destino)
                return;
            NodoArista* eliminada = *enlace;
            *enlace = eliminada->siguiente;
            delete eliminada;
        }
    }

    // Reinicia las marcas y predecesores usados por BFS.
    void reiniciarBusqueda()
    {
        NodoVertice* actual = vertices;
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            actual->visitado = false;
            actual->anterior = nullptr;
            actual = actual->siguiente;
        }
    }

    // Libera todas las aristas de un vértice.
    static void destruirAristas(NodoVertice* vertice)
    {
        while (vertice->aristas != nullptr)
        {
            NodoArista* eliminada = vertice->aristas;
            vertice->aristas = eliminada->siguiente;
            delete eliminada;
        }
    }

    // Libera todos los vértices y sus aristas.
    void limpiarVertices()
    {
        while (vertices != nullptr)
        {
            NodoVertice* eliminado = vertices;
            vertices = vertices->siguiente;
            destruirAristas(eliminado);
            delete eliminado;
        }
        cantidad = 0;
    }

public:
    // Crea un grafo vacío con un índice hash.
    Grafo()
    {
        vertices = nullptr;
        cantidad = 0;
    }

    // Libera todos los vértices y sus aristas.
    ~Grafo()
    {
        limpiarVertices();
    }

    // Agrega un vértice nuevo.
    bool agregarVertice(Vertice dato)
    {
        if (indice.buscar(dato) != nullptr)
            return false;

        NodoVertice* nuevo = new NodoVertice(dato);
        try
        {
            if (!indice.insertar(dato, nuevo))
            {
                delete nuevo;
                return false;
            }
        }
        catch (...)
        {
            delete nuevo;
            throw;
        }

        nuevo->siguiente = vertices;
        vertices = nuevo;
        ++cantidad;
        return true;
    }

    // Conecta dos vértices en ambas direcciones.
    bool conectar(Vertice primero, Vertice segundo)
    {
        NodoVertice** origenEncontrado = indice.buscar(primero);
        NodoVertice** destinoEncontrado = indice.buscar(segundo);
        if (origenEncontrado == nullptr || destinoEncontrado == nullptr
            || *origenEncontrado == *destinoEncontrado
            || contieneArista(*origenEncontrado, *destinoEncontrado))
            return false;

        NodoArista* haciaSegundo = new NodoArista(*destinoEncontrado);
        NodoArista* haciaPrimero = nullptr;
        try
        {
            haciaPrimero = new NodoArista(*origenEncontrado);
        }
        catch (...)
        {
            delete haciaSegundo;
            throw;
        }

        haciaSegundo->siguiente = (*origenEncontrado)->aristas;
        (*origenEncontrado)->aristas = haciaSegundo;
        haciaPrimero->siguiente = (*destinoEncontrado)->aristas;
        (*destinoEncontrado)->aristas = haciaPrimero;
        return true;
    }

    // Elimina un vértice y sus conexiones.
    bool eliminarVertice(Vertice dato)
    {
        NodoVertice** encontrado = indice.buscar(dato);
        if (encontrado == nullptr)
            return false;
        NodoVertice* eliminado = *encontrado;

        NodoVertice* actual = vertices;
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (actual != eliminado)
                quitarArista(actual, eliminado);
            actual = actual->siguiente;
        }

        NodoVertice** enlace = &vertices;
        while (*enlace != eliminado)
            enlace = &(*enlace)->siguiente;
        *enlace = eliminado->siguiente;

        indice.eliminar(dato);
        destruirAristas(eliminado);
        delete eliminado;
        --cantidad;
        return true;
    }

    // Busca por BFS el camino con menos aristas.
    bool caminoMinimo(Vertice origen, Vertice destino, ListaEnlazada<Vertice>& camino)
    {
        camino.limpiar();
        reiniciarBusqueda();

        NodoVertice** inicio = indice.buscar(origen);
        NodoVertice** fin = indice.buscar(destino);
        if (inicio == nullptr || fin == nullptr)
            return false;

        Cola<NodoVertice*> pendientes;
        (*inicio)->visitado = true;
        pendientes.encolar(*inicio);

        NodoVertice* actual = nullptr;
        while (pendientes.desencolar(actual))
        {
            if (actual == *fin)
                break;
            NodoArista* arista = actual->aristas;
            size_t i;
            for (i = 0; i < cantidad; ++i)
            {
                if (arista == nullptr)
                    break;
                if (!arista->destino->visitado)
                {
                    arista->destino->visitado = true;
                    arista->destino->anterior = actual;
                    pendientes.encolar(arista->destino);
                }
                arista = arista->siguiente;
            }
        }

        bool encontrado = (*fin)->visitado;
        if (encontrado)
        {
            actual = *fin;
            size_t i;
            for (i = 0; i < cantidad; ++i)
            {
                if (actual == nullptr)
                    break;
                camino.insertarAlInicio(actual->dato);
                actual = actual->anterior;
            }
        }
        reiniciarBusqueda();
        return encontrado;
    }

    // Indica si el grafo contiene el vértice.
    bool contiene(Vertice dato) const
    {
        return indice.buscar(dato) != nullptr;
    }

    // Devuelve la cantidad de vértices.
    size_t cantidadVertices() const
    {
        return cantidad;
    }
};

#endif
