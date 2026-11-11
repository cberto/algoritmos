#ifndef ESTRUCTURAS_LISTA_ENLAZADA_H
#define ESTRUCTURAS_LISTA_ENLAZADA_H

#include <cstddef>

using namespace std;

template <typename T>
class ListaEnlazada
{
private:
    struct Nodo
    {
        T dato;
        Nodo* siguiente;

        // Guarda el dato y deja el enlace vacío.
        Nodo(T valor)
        {
            dato = valor;
            siguiente = nullptr;
        }
    };

    Nodo* primero;
    Nodo* ultimo;
    size_t cantidad;

public:
    // Crea una lista vacía.
    ListaEnlazada()
    {
        primero = nullptr;
        ultimo = nullptr;
        cantidad = 0;
    }

    // Libera todos los nodos.
    ~ListaEnlazada()
    {
        limpiar();
    }

    // Indica si no hay elementos.
    bool vacia() const
    {
        return primero == nullptr;
    }

    // Devuelve la cantidad de elementos.
    size_t tamano() const
    {
        return cantidad;
    }

    // Inserta un elemento al comienzo.
    void insertarAlInicio(T dato)
    {
        Nodo* nuevo = new Nodo(dato);
        nuevo->siguiente = primero;
        primero = nuevo;
        if (ultimo == nullptr)
            ultimo = nuevo;
        ++cantidad;
    }

    // Inserta un elemento al final.
    void insertarAlFinal(T dato)
    {
        Nodo* nuevo = new Nodo(dato);
        if (ultimo == nullptr)
            primero = nuevo;
        else
            ultimo->siguiente = nuevo;
        ultimo = nuevo;
        ++cantidad;
    }

    // Copia el elemento de la posición indicada en dato.
    bool obtener(size_t posicion, T& dato) const
    {
        if (posicion >= cantidad)
            return false;

        Nodo* actual = primero;
        size_t i;
        for (i = 0; i < posicion; ++i)
            actual = actual->siguiente;

        dato = actual->dato;
        return true;
    }

    // Quita el primer elemento y lo devuelve en dato.
    bool eliminarPrimero(T& dato)
    {
        if (primero == nullptr)
            return false;

        Nodo* eliminado = primero;
        dato = eliminado->dato;
        primero = eliminado->siguiente;
        if (primero == nullptr)
            ultimo = nullptr;
        delete eliminado;
        --cantidad;
        return true;
    }

    // Elimina la primera aparición del dato.
    bool eliminar(T dato)
    {
        Nodo* anterior = nullptr;
        Nodo* actual = primero;

        while (actual != nullptr && !(actual->dato == dato))
        {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual == nullptr)
            return false;

        if (anterior == nullptr)
            primero = actual->siguiente;
        else
            anterior->siguiente = actual->siguiente;
        if (ultimo == actual)
            ultimo = anterior;

        delete actual;
        --cantidad;
        return true;
    }

    // Libera los nodos y deja la lista vacía.
    void limpiar()
    {
        while (primero != nullptr)
        {
            Nodo* eliminado = primero;
            primero = primero->siguiente;
            delete eliminado;
        }
        ultimo = nullptr;
        cantidad = 0;
    }

    // Llama a visitar una vez por cada elemento.
    void recorrer(void (*visitar)(T)) const
    {
        Nodo* actual = primero;
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            visitar(actual->dato);
            actual = actual->siguiente;
        }
    }
};

#endif
