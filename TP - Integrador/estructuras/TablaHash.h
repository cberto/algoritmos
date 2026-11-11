#ifndef ESTRUCTURAS_TABLA_HASH_H
#define ESTRUCTURAS_TABLA_HASH_H

#include <cstddef>
#include <stdexcept>
#include "FuncionHash.h"

using namespace std;

template <typename Clave, typename Valor, typename Hash = FuncionHash<Clave>>
class TablaHash
{
private:
    struct Nodo
    {
        Clave clave;
        Valor valor;
        Nodo* siguiente;

        // Guarda clave, valor y el enlace siguiente.
        Nodo(Clave claveNueva, Valor valorNuevo, Nodo* proximo)
        {
            clave = claveNueva;
            valor = valorNuevo;
            siguiente = proximo;
        }
    };

    Nodo** buckets;
    size_t capacidad;
    size_t cantidad;
    size_t colisiones;

    // Libera los nodos sin borrar el arreglo de buckets.
    void limpiar()
    {
        size_t i;
        for (i = 0; i < capacidad; ++i)
        {
            while (buckets[i] != nullptr)
            {
                Nodo* eliminado = buckets[i];
                buckets[i] = eliminado->siguiente;
                delete eliminado;
            }
        }
        cantidad = 0;
        colisiones = 0;
    }

    // Devuelve el bucket correspondiente a una clave.
    size_t posicion(Clave clave) const
    {
        return Hash{}(clave) % capacidad;
    }

public:
    // Crea la tabla con la cantidad indicada de buckets.
    TablaHash(size_t cantidadBuckets = 11)
    {
        buckets = nullptr;
        capacidad = cantidadBuckets;
        cantidad = 0;
        colisiones = 0;

        if (capacidad == 0)
            throw invalid_argument("La tabla hash necesita al menos un bucket.");
        buckets = new Nodo*[capacidad]();
    }

    // Libera los nodos y el arreglo de buckets.
    ~TablaHash()
    {
        limpiar();
        delete[] buckets;
    }

    // Inserta una clave nueva; devuelve false si ya existe.
    bool insertar(Clave clave, Valor valor)
    {
        size_t indice = posicion(clave);
        Nodo* actual = buckets[indice];
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (actual == nullptr)
                break;
            if (actual->clave == clave)
                return false;
            actual = actual->siguiente;
        }

        Nodo* nuevo = new Nodo(clave, valor, buckets[indice]);
        if (buckets[indice] != nullptr)
            ++colisiones;
        buckets[indice] = nuevo;
        ++cantidad;
        return true;
    }

    // Devuelve la dirección del valor o null si no existe.
    Valor* buscar(Clave clave)
    {
        Nodo* actual = buckets[posicion(clave)];
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (actual == nullptr)
                break;
            if (actual->clave == clave)
                return &actual->valor;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Busca una clave sin modificar el valor encontrado.
    const Valor* buscar(Clave clave) const
    {
        Nodo* actual = buckets[posicion(clave)];
        size_t i;
        for (i = 0; i < cantidad; ++i)
        {
            if (actual == nullptr)
                break;
            if (actual->clave == clave)
                return &actual->valor;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Elimina una clave; devuelve false si no existe.
    bool eliminar(Clave clave)
    {
        Nodo** enlace = &buckets[posicion(clave)];
        while (*enlace != nullptr && !((*enlace)->clave == clave))
            enlace = &(*enlace)->siguiente;
        if (*enlace == nullptr)
            return false;

        Nodo* eliminado = *enlace;
        *enlace = eliminado->siguiente;
        delete eliminado;
        --cantidad;
        return true;
    }

    // Indica si la tabla está vacía.
    bool vacia() const
    {
        return cantidad == 0;
    }

    // Devuelve la cantidad de entradas.
    size_t tamano() const
    {
        return cantidad;
    }

    // Devuelve la cantidad de buckets.
    size_t cantidadBuckets() const
    {
        return capacidad;
    }

    // Devuelve las inserciones que encontraron ocupado su bucket.
    size_t cantidadColisiones() const
    {
        return colisiones;
    }

    // Devuelve entradas divididas por buckets.
    double factorCarga() const
    {
        return static_cast<double>(cantidad) / capacidad;
    }

};

#endif
