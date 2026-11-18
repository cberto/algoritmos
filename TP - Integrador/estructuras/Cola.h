#ifndef ESTRUCTURAS_COLA_H
#define ESTRUCTURAS_COLA_H

using namespace std;

template <typename T>
class Cola
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

    Nodo* frente;
    Nodo* final;
    int cantidad;

    // Libera todos los nodos de la cola.
    void limpiar()
    {
        while (frente != nullptr)
        {
            Nodo* eliminado = frente;
            frente = frente->siguiente;
            delete eliminado;
        }
        final = nullptr;
        cantidad = 0;
    }

public:
    // Crea una cola vacía.
    Cola()
    {
        frente = nullptr;
        final = nullptr;
        cantidad = 0;
    }

    // Libera todos los nodos.
    ~Cola()
    {
        limpiar();
    }

    // Indica si no hay elementos.
    bool vacia()
    {
        return frente == nullptr;
    }

    // Devuelve la cantidad de elementos.
    int tamano()
    {
        return cantidad;
    }

    // Agrega un elemento al final de la cola.
    void encolar(T dato)
    {
        Nodo* nuevo = new Nodo(dato);
        if (final == nullptr)
            frente = nuevo;
        else
            final->siguiente = nuevo;
        final = nuevo;
        ++cantidad;
    }

    // Quita el primero y lo devuelve en dato.
    bool desencolar(T& dato)
    {
        if (frente == nullptr)
            return false;

        Nodo* eliminado = frente;
        dato = eliminado->dato;
        frente = eliminado->siguiente;
        if (frente == nullptr)
            final = nullptr;
        delete eliminado;
        --cantidad;
        return true;
    }

    // Copia el primer elemento en dato sin quitarlo.
    bool consultarFrente(T& dato)
    {
        if (frente == nullptr)
            return false;
        dato = frente->dato;
        return true;
    }
};

#endif
